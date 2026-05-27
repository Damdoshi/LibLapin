// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// LibLapin pool unit tests

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lapin.h"

#define CHECK(expr)                                                     \
  do                                                                    \
    {                                                                   \
      if (!(expr))                                                      \
        {                                                               \
          fprintf(stderr, "[pool_unit] %s:%d: check failed: %s\n",      \
                  __FILE__, __LINE__, #expr);                           \
          return (false);                                               \
        }                                                               \
    }                                                                   \
  while (0)

#define CHECK_EQ(a, b)                                                   \
  do                                                                    \
    {                                                                   \
      size_t _a = (size_t)(a);                                           \
      size_t _b = (size_t)(b);                                           \
      if (_a != _b)                                                      \
        {                                                               \
          fprintf(stderr, "[pool_unit] %s:%d: check failed: %s == %s"   \
                  " (%zu != %zu)\n", __FILE__, __LINE__, #a, #b, _a, _b); \
          return (false);                                               \
        }                                                               \
    }                                                                   \
  while (0)

struct AlignNode
{
  max_align_t alignment;
  int value;
};

struct Node
{
  int value;
  int marker;
};

struct PoolStats
{
  int ctor_calls;
  int ctor_successes;
  int ctor_failures;
  int dtor_calls;
  int dtor_sum;
};

struct CtorParam
{
  PoolStats *stats;
  int value;
  bool fail;
};

struct ForeachState
{
  t_bunny_pool *pool;
  int values[32];
  int count;
  bool free_even;
};

extern "C" bool pool_ctor(void *data, void *param)
{
  Node *node = (Node*)data;
  CtorParam *ctor = (CtorParam*)param;

  ctor->stats->ctor_calls += 1;
  if (ctor->fail)
    {
      ctor->stats->ctor_failures += 1;
      return (false);
    }
  node->value = ctor->value;
  node->marker = 0xBEEF;
  ctor->stats->ctor_successes += 1;
  return (true);
}

static PoolStats *gl_dtor_stats = NULL;

extern "C" void pool_dtor(void *data)
{
  Node *node = (Node*)data;

  if (gl_dtor_stats)
    {
      gl_dtor_stats->dtor_calls += 1;
      gl_dtor_stats->dtor_sum += node->value;
    }
  node->marker = 0;
}

extern "C" void collect_value(void *data, void *param)
{
  Node *node = (Node*)data;
  ForeachState *state = (ForeachState*)param;

  if ((size_t)state->count < sizeof(state->values) / sizeof(state->values[0]))
    state->values[state->count] = node->value;
  state->count += 1;
}

extern "C" void collect_and_maybe_free(void *data, void *param)
{
  Node *node = (Node*)data;
  ForeachState *state = (ForeachState*)param;

  if ((size_t)state->count < sizeof(state->values) / sizeof(state->values[0]))
    state->values[state->count] = node->value;
  state->count += 1;
  if (state->free_even && node->value % 2 == 0)
    bunny_pool_free(state->pool, node);
}

static bool has_value(t_bunny_pool *pool, int value)
{
  size_t i;

  for (i = 0; i < bunny_pool_size(pool); ++i)
    if (bunny_pool_get(pool, i, Node)->value == value)
      return (true);
  return (false);
}

static bool test_capacity_sizes_alignment(void)
{
  t_bunny_pool *pool;
  AlignNode *a;
  AlignNode *b;
  AlignNode *c;
  AlignNode *d;
  size_t id_a;
  size_t id_b;
  size_t id_c;

  pool = bunny_new_pool(3, AlignNode);
  CHECK(pool != NULL);
  CHECK_EQ(bunny_pool_capacity(pool), 3);
  CHECK_EQ(bunny_pool_size(pool), 0);
  CHECK(bunny_pool_empty(pool));
  CHECK_EQ(bunny_pool_elem_size(pool), sizeof(AlignNode));
  CHECK(bunny_pool_elem_alloc_size(pool) >= sizeof(AlignNode) + sizeof(size_t));
  CHECK_EQ(bunny_pool_elem_alloc_size(pool) % alignof(max_align_t), 0);

  a = (AlignNode*)bunny_pool_getv(pool, &id_a);
  b = (AlignNode*)bunny_pool_getv(pool, &id_b);
  c = (AlignNode*)bunny_pool_getv(pool, &id_c);
  d = bunny_pool_new(pool, AlignNode);
  CHECK(a != NULL);
  CHECK(b != NULL);
  CHECK(c != NULL);
  CHECK(d == NULL);
  CHECK_EQ(bunny_pool_size(pool), 3);
  CHECK(!bunny_pool_empty(pool));
  CHECK_EQ((uintptr_t)a % alignof(max_align_t), 0);
  CHECK_EQ((uintptr_t)b % alignof(max_align_t), 0);
  CHECK_EQ((uintptr_t)c % alignof(max_align_t), 0);
  CHECK(bunny_pool_elem_is_valid(pool, a));
  CHECK(bunny_pool_elem_is_valid(pool, b));
  CHECK(bunny_pool_elem_is_valid(pool, c));
  CHECK_EQ(bunny_pool_elem_index(a), id_a);
  CHECK_EQ(bunny_pool_elem_index(b), id_b);
  CHECK_EQ(bunny_pool_elem_index(c), id_c);

  bunny_delete_pool(pool);
  return (true);
}

static bool test_free_validation_and_dense_swap(void)
{
  t_bunny_pool *pool;
  Node *a;
  Node *b;
  Node *c;
  Node foreign;
  size_t b_index;
  size_t c_index;
  size_t size;

  pool = bunny_new_pool(4, Node);
  CHECK(pool != NULL);
  a = bunny_pool_new(pool, Node);
  b = bunny_pool_new(pool, Node);
  c = bunny_pool_new(pool, Node);
  CHECK(a != NULL && b != NULL && c != NULL);
  a->value = 1;
  b->value = 2;
  c->value = 3;
  b_index = bunny_pool_elem_index(b);
  c_index = bunny_pool_elem_index(c);
  CHECK_EQ(bunny_pool_size(pool), 3);

  bunny_pool_free(pool, b);
  CHECK_EQ(bunny_pool_size(pool), 2);
  CHECK(!bunny_pool_elem_is_valid(pool, b));
  CHECK(bunny_pool_elem_is_valid(pool, a));
  CHECK(bunny_pool_elem_is_valid(pool, c));
  CHECK_EQ(bunny_pool_elem_index(c), b_index);
  CHECK_EQ(bunny_pool_get(pool, b_index, Node), c);
  CHECK_EQ(bunny_pool_elem_index(b), c_index);

  size = bunny_pool_size(pool);
  bunny_pool_free(pool, b); // double free must not corrupt the pool.
  CHECK_EQ(bunny_pool_size(pool), size);

  memset(&foreign, 0, sizeof(foreign));
  bunny_pool_free(pool, &foreign); // foreign pointer must be rejected.
  CHECK_EQ(bunny_pool_size(pool), size);
  CHECK(!bunny_pool_elem_is_valid(pool, &foreign));

  bunny_pool_free(pool, ((char*)a) + 1); // interior pointer must be rejected.
  CHECK_EQ(bunny_pool_size(pool), size);
  CHECK(bunny_pool_elem_is_valid(pool, a));

  bunny_delete_pool(pool);
  return (true);
}

static bool test_ctor_dtor_clear_delete(void)
{
  PoolStats stats;
  CtorParam def;
  CtorParam custom;
  CtorParam failing;
  t_bunny_pool *pool;
  Node *a;
  Node *b;
  Node *c;
  Node *d;

  memset(&stats, 0, sizeof(stats));
  gl_dtor_stats = &stats;
  def = {&stats, 10, false};
  custom = {&stats, 20, false};
  failing = {&stats, 99, true};

  pool = bunny_build_pool(4, Node, pool_ctor, pool_dtor, &def);
  CHECK(pool != NULL);
  a = bunny_pool_new(pool, Node);
  b = bunny_pool_new_param(pool, Node, &custom);
  CHECK(a != NULL && b != NULL);
  CHECK_EQ(a->value, 10);
  CHECK_EQ(b->value, 20);
  CHECK_EQ(a->marker, 0xBEEF);
  CHECK_EQ(b->marker, 0xBEEF);
  CHECK_EQ(stats.ctor_calls, 2);
  CHECK_EQ(stats.ctor_successes, 2);
  CHECK_EQ(stats.ctor_failures, 0);
  CHECK_EQ(bunny_pool_size(pool), 2);

  c = bunny_pool_new_param(pool, Node, &failing);
  CHECK(c == NULL);
  CHECK_EQ(stats.ctor_calls, 3);
  CHECK_EQ(stats.ctor_successes, 2);
  CHECK_EQ(stats.ctor_failures, 1);
  CHECK_EQ(stats.dtor_calls, 0);
  CHECK_EQ(bunny_pool_size(pool), 2);

  bunny_pool_free(pool, a);
  CHECK_EQ(stats.dtor_calls, 1);
  CHECK_EQ(stats.dtor_sum, 10);
  CHECK_EQ(bunny_pool_size(pool), 1);

  c = bunny_pool_new_param(pool, Node, &custom);
  CHECK(c != NULL);
  CHECK_EQ(c->value, 20);
  CHECK_EQ(bunny_pool_size(pool), 2);
  bunny_pool_clear(pool);
  CHECK_EQ(stats.dtor_calls, 3);
  CHECK_EQ(stats.dtor_sum, 50);
  CHECK_EQ(bunny_pool_size(pool), 0);
  CHECK(bunny_pool_empty(pool));

  d = bunny_pool_new(pool, Node);
  CHECK(d != NULL);
  CHECK_EQ(d->value, 10);
  bunny_delete_pool(pool);
  CHECK_EQ(stats.dtor_calls, 4);
  CHECK_EQ(stats.dtor_sum, 60);
  gl_dtor_stats = NULL;
  bunny_delete_pool(NULL);
  return (true);
}

static bool test_foreach_variants(void)
{
  t_bunny_pool *pool;
  Node *nodes[5];
  ForeachState state;
  size_t i;

  pool = bunny_new_pool(8, Node);
  CHECK(pool != NULL);
  for (i = 0; i < 5; ++i)
    {
      nodes[i] = bunny_pool_new(pool, Node);
      CHECK(nodes[i] != NULL);
      nodes[i]->value = (int)i;
      nodes[i]->marker = 0xCAFE;
    }

  memset(&state, 0, sizeof(state));
  bunny_pool_foreach(pool, collect_value, &state);
  CHECK_EQ(state.count, 5);
  for (i = 0; i < 5; ++i)
    CHECK_EQ(state.values[i], i);

  memset(&state, 0, sizeof(state));
  bunny_pool_foreach_reverse(pool, collect_value, &state);
  CHECK_EQ(state.count, 5);
  for (i = 0; i < 5; ++i)
    CHECK_EQ(state.values[i], 4 - i);

  memset(&state, 0, sizeof(state));
  state.pool = pool;
  state.free_even = true;
  bunny_pool_foreach_safe(pool, collect_and_maybe_free, &state);
  CHECK_EQ(state.count, 5);
  CHECK_EQ(state.values[0], 4);
  CHECK_EQ(state.values[1], 3);
  CHECK_EQ(state.values[2], 2);
  CHECK_EQ(state.values[3], 1);
  CHECK_EQ(state.values[4], 0);
  CHECK_EQ(bunny_pool_size(pool), 2);
  CHECK(has_value(pool, 1));
  CHECK(has_value(pool, 3));
  CHECK(!has_value(pool, 0));
  CHECK(!has_value(pool, 2));
  CHECK(!has_value(pool, 4));

  bunny_delete_pool(pool);
  return (true);
}

static bool test_zero_capacity_pool(void)
{
  t_bunny_pool *pool;
  Node *node;

  pool = bunny_new_pool(0, Node);
  CHECK(pool != NULL);
  CHECK_EQ(bunny_pool_capacity(pool), 0);
  CHECK_EQ(bunny_pool_size(pool), 0);
  CHECK(bunny_pool_empty(pool));
  node = bunny_pool_new(pool, Node);
  CHECK(node == NULL);
  bunny_pool_clear(pool);
  CHECK_EQ(bunny_pool_size(pool), 0);
  bunny_delete_pool(pool);
  return (true);
}

int main(void)
{
  struct Test
  {
    const char *name;
    bool (*func)(void);
  } tests[] = {
    {"capacity, sizes and alignment", test_capacity_sizes_alignment},
    {"free validation and dense swap", test_free_validation_and_dense_swap},
    {"constructor, destructor, clear and delete", test_ctor_dtor_clear_delete},
    {"foreach, reverse foreach and safe foreach", test_foreach_variants},
    {"zero capacity pool", test_zero_capacity_pool}
  };
  size_t i;

  for (i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i)
    {
      fprintf(stderr, "[pool_unit] running %s\n", tests[i].name);
      if (!tests[i].func())
        return (1);
    }
  fprintf(stderr, "[pool_unit] all tests passed\n");
  return (0);
}
