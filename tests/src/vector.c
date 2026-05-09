/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
** Pentacle Technologie 2008-2026
** EFRITS 2022-2026
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#include		<stdlib.h>
#include		"lapin.h"

typedef struct		s_item
{
  int			magic;
  int			value;
} 			t_item;

typedef struct		s_counter
{
  int			ctor;
  int			dtor;
  int			fail_after;
  int			value;
} 			t_counter;

static bool		item_ctor(void			*data,
				  void			*param)
{
  t_item		*item = (t_item*)data;
  t_counter		*counter = (t_counter*)param;

  assert(counter != NULL);
  if (counter->fail_after >= 0 && counter->ctor >= counter->fail_after)
    return (false);
  item->magic = 0xBEEF;
  item->value = counter->value + counter->ctor;
  counter->ctor += 1;
  return (true);
}

static bool		item_dtor(void			*data)
{
  t_item		*item = (t_item*)data;

  assert(item->magic == 0xBEEF);
  item->magic = 0xDEAD;
  return (true);
}

static void		increment_item(void			*data,
				       void			*param)
{
  t_item		*item = (t_item*)data;

  assert(param == (void*)0x2020);
  assert(item->magic == 0xBEEF);
  item->value += 1;
}

static int		compare_item_value(const void		*a,
					   const void		*b,
					   void			*param)
{
  const t_item		*ia = (const t_item*)a;
  const t_item		*ib = (const t_item*)b;

  assert(param == (void*)0x8484);
  return (ia->value - ib->value);
}

static void		free_list_payloads(t_bunny_list		*lst)
{
  t_bunny_node		*nod;

  for (bunny_list_all(lst, nod))
    bunny_free(bunny_list_data(nod, void*));
}

static void		test_empty_and_plain_vector(void)
{
  t_bunny_vector	*vec;
  size_t		i;

  assert((vec = bunny_new_vector(0, int)) != NULL);
  assert(bunny_vector_empty(vec));
  assert(bunny_vector_size(vec) == 0);
  assert(bunny_vector_elem_size(vec) == sizeof(int));
  bunny_delete_vector(vec);

  assert((vec = bunny_new_vector(6, int)) != NULL);
  assert(!bunny_vector_empty(vec));
  assert(bunny_vector_size(vec) == 6);
  assert(bunny_vector_elem_size(vec) == sizeof(int));
  for (i = 0; i < bunny_vector_size(vec); ++i)
    {
      bunny_vector_data(vec, i, int) = (int)(i * 3);
      assert(*(int*)bunny_vector_address(vec, i) == (int)(i * 3));
    }
  for (i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, int) == (int)(i * 3));
  bunny_delete_vector(vec);
}

static void		test_build_resize_crop_and_destructors(void)
{
  t_bunny_vector	*vec;
  t_counter		counter = {0, 0, -1, 100};
  size_t		i;

  assert((vec = bunny_build_vector(2, t_item, item_ctor, item_dtor, &counter)) != NULL);
  assert(counter.ctor == 2);
  assert(bunny_vector_size(vec) == 2);
  assert(bunny_vector_data(vec, 0, t_item).value == 100);
  assert(bunny_vector_data(vec, 1, t_item).value == 101);

  assert((vec = bunny_vector_resize(vec, 3, &counter)) != NULL);
  assert(counter.ctor == 3);
  assert(bunny_vector_size(vec) == 3);
  assert(bunny_vector_data(vec, 2, t_item).magic == 0xBEEF);
  assert(bunny_vector_data(vec, 2, t_item).value == 102);

  assert((vec = bunny_vector_resize(vec, 8, &counter)) != NULL);
  assert(counter.ctor == 8);
  assert(bunny_vector_size(vec) == 8);
  for (i = 0; i < bunny_vector_size(vec); ++i)
    {
      assert(bunny_vector_data(vec, i, t_item).magic == 0xBEEF);
      assert(bunny_vector_data(vec, i, t_item).value == (int)(100 + i));
    }

  assert((vec = bunny_vector_resize(vec, 4, &counter)) != NULL);
  assert(bunny_vector_size(vec) == 4);
  assert((vec = bunny_vector_crop(vec)) != NULL);
  assert(bunny_vector_size(vec) == 4);
  assert((vec = bunny_vector_resize(vec, 6, &counter)) != NULL);
  assert(bunny_vector_size(vec) == 6);
  for (i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, t_item).magic == 0xBEEF);
  bunny_delete_vector(vec);
}

static void		test_sort_foreach_fast_foreach_and_untie(void)
{
  t_bunny_vector	*vec;
  t_bunny_list		*lst;
  t_bunny_node		*nod;
  t_bunny_threadpool	*pool;
  int			values[6] = {5, 1, 4, 2, 6, 3};
  size_t		i;

  assert((vec = bunny_new_vector(NBRCELL(values), t_item)) != NULL);
  for (i = 0; i < NBRCELL(values); ++i)
    {
      bunny_vector_data(vec, i, t_item).magic = 0xBEEF;
      bunny_vector_data(vec, i, t_item).value = values[i];
    }
  bunny_vector_sort(vec, compare_item_value, (void*)0x8484);
  for (i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, t_item).value == (int)(i + 1));

  bunny_vector_foreach(vec, increment_item, (void*)0x2020);
  for (i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, t_item).value == (int)(i + 2));
  assert((pool = bunny_new_threadpool(2)) != NULL);
  assert(bunny_vector_fast_foreach(pool, vec, increment_item, (void*)0x2020));
  bunny_delete_threadpool(pool);
  for (i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, t_item).value == (int)(i + 3));

  assert((lst = bunny_vector_untie(vec)) != NULL);
  assert(bunny_list_size(lst) == bunny_vector_size(vec));
  i = 0;
  for (bunny_list_all(lst, nod))
    {
      t_item		*copy = bunny_list_data(nod, t_item*);

      assert(copy != bunny_vector_address(vec, i));
      assert(copy->magic == 0xBEEF);
      assert(copy->value == bunny_vector_data(vec, i, t_item).value);
      copy->value += 1000;
      assert(copy->value != bunny_vector_data(vec, i, t_item).value);
      ++i;
    }
  assert(i == bunny_vector_size(vec));
  free_list_payloads(lst);
  bunny_delete_list(lst);
  bunny_delete_vector(vec);
}

static void		test_constructor_failure_rolls_back(void)
{
  t_bunny_vector	*vec;
  t_counter		counter = {0, 0, 3, 50};

  assert(bunny_build_vector(5, t_item, item_ctor, item_dtor, &counter) == NULL);
  assert(counter.ctor == 3);

  counter.ctor = 0;
  counter.fail_after = -1;
  assert((vec = bunny_build_vector(2, t_item, item_ctor, item_dtor, &counter)) != NULL);
  counter.fail_after = counter.ctor + 1;
  {
    t_bunny_vector	*tmp = bunny_vector_resize(vec, 4, &counter);

    assert(tmp != NULL);
    vec = tmp;
  }
  assert(bunny_vector_size(vec) == 2);
  bunny_delete_vector(vec);
}

static void		test_allocation_failures(void)
{
  t_bunny_vector	*vec;

  bunny_malloc_failure(true);
  assert(bunny_new_vector(3, int) == NULL);
  bunny_malloc_failure(false);

  assert((vec = bunny_new_vector(2, int)) != NULL);
  bunny_malloc_failure(true);
  assert(bunny_vector_resize(vec, 100, NULL) == NULL);
  bunny_malloc_failure(false);
  bunny_delete_vector(vec);
}

int			main(void)
{
  test_empty_and_plain_vector();
  test_build_resize_crop_and_destructors();
  test_sort_foreach_fast_foreach_and_untie();
  test_constructor_failure_rolls_back();
  test_allocation_failures();
  return (EXIT_SUCCESS);
}
