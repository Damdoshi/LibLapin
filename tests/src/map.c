/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
** Pentacle Technologie 2008-2026
** EFRITS 2022-2026
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#include		<stdint.h>
#include		<stdlib.h>
#include		"lapin.h"

typedef struct		s_map_check
{
  int			count;
  int			sum_keys;
  int			sum_values;
} 			t_map_check;

static void		check_int_node(t_bunny_map		*node,
				       void			*param)
{
  t_map_check		*check = (t_map_check*)param;

  assert(node != NULL);
  assert(bunny_map_data(node, int*) != NULL);
  check->count += 1;
  check->sum_keys += (int)(intptr_t)node->key;
  check->sum_values += *bunny_map_data(node, int*);
}

static void		increment_int_node(t_bunny_map		*node,
					 void			*param)
{
  assert(param == (void*)0x2020);
  *bunny_map_data(node, int*) += 1;
}

static void		test_empty_map_does_not_create_on_get(void)
{
  t_bunny_map		*map;

  assert((map = bunny_new_map(int_map)) != NULL);
  assert(bunny_map_size(map) == 0);
  assert(bunny_map_empty(map));
  assert(bunny_map_get_data(map, 42, int*) == NULL);
  assert(bunny_map_get_subtree(map, (void*)(intptr_t)42, false) == NULL);
  assert(bunny_map_size(map) == 0);
  assert(bunny_map_empty(map));
  assert(bunny_delete_map(map) == 0);
}

static void		test_int_map_set_get_replace_iterate_and_clear(void)
{
  t_bunny_map		*map;
  t_bunny_map		**it;
  t_bunny_map		*node;
  t_map_check		check;
  int			values[6] = {50, 10, 90, 30, 70, 42};
  int			replacement = 300;
  int			keys[5] = {5, 1, 9, 3, 7};
  int			expected_keys[5] = {1, 3, 5, 7, 9};
  size_t		i;

  assert((map = bunny_new_map(int_map)) != NULL);
  for (i = 0; i < NBRCELL(keys); ++i)
    {
      assert(bunny_map_set_data(map, keys[i], &values[i], int*) == &values[i]);
      assert(bunny_map_size(map) == i + 1);
      assert(!bunny_map_empty(map));
    }
  for (i = 0; i < NBRCELL(keys); ++i)
    assert(bunny_map_get_data(map, keys[i], int*) == &values[i]);

  assert(bunny_map_set_data(map, 3, &replacement, int*) == &values[3]);
  assert(bunny_map_size(map) == NBRCELL(keys));
  assert(bunny_map_get_data(map, 3, int*) == &replacement);
  assert(bunny_map_get_data(map, 404, int*) == NULL);
  assert(bunny_map_size(map) == NBRCELL(keys));

  assert((node = bunny_map_get_subtree(map, (void*)(intptr_t)9, false)) != NULL);
  assert(bunny_map_data(node, int*) == &values[2]);
  assert(bunny_map_get_subtree(map, (void*)(intptr_t)404, false) == NULL);
  assert((node = bunny_map_get_subtree(map, (void*)(intptr_t)42, true)) != NULL);
  assert(bunny_map_size(map) == NBRCELL(keys) + 1);
  assert(bunny_map_data(node, int*) == NULL);

  i = 0;
  for (bunny_map_all(map, it))
    {
      assert(i < NBRCELL(expected_keys));
      assert((int)(intptr_t)(*it)->key == expected_keys[i]);
      assert(bunny_map_data(*it, int*) != NULL);
      ++i;
    }
  assert(i == NBRCELL(expected_keys));

  check.count = 0;
  check.sum_keys = 0;
  check.sum_values = 0;
  bunny_map_foreach(map, check_int_node, &check);
  assert(check.count == 5);
  assert(check.sum_keys == 1 + 3 + 5 + 7 + 9);
  assert(check.sum_values == 10 + 300 + 50 + 70 + 90);

  assert(bunny_map_clear(map) == NBRCELL(keys) + 1);
  assert(bunny_map_size(map) == 0);
  assert(bunny_map_empty(map));
  assert(bunny_map_get_data(map, 1, int*) == NULL);
  assert(bunny_map_set_data(map, 2, &values[5], int*) == &values[5]);
  assert(bunny_map_size(map) == 1);
  assert(bunny_map_get_data(map, 2, int*) == &values[5]);
  assert(bunny_delete_map(map) == 1);
}

static void		test_fast_foreach(void)
{
  t_bunny_map		*map;
  t_bunny_threadpool	*pool;
  int			values[4] = {1, 2, 3, 4};
  int			keys[4] = {4, 2, 1, 3};
  size_t		i;

  assert((map = bunny_new_map(int_map)) != NULL);
  for (i = 0; i < NBRCELL(keys); ++i)
    assert(bunny_map_set_data(map, keys[i], &values[i], int*) == &values[i]);
  assert((pool = bunny_new_threadpool(2)) != NULL);
  assert(bunny_map_fast_foreach(pool, map, increment_int_node, (void*)0x2020));
  bunny_delete_threadpool(pool);
  for (i = 0; i < NBRCELL(values); ++i)
    assert(values[i] == (int)i + 2);
  assert(bunny_delete_map(map) == NBRCELL(values));
}

static void		test_allocation_failure(void)
{
  t_bunny_map		*map;
  int			value = 12;

  bunny_malloc_failure(true);
  assert(bunny_new_map(int_map) == NULL);
  bunny_malloc_failure(false);

  assert((map = bunny_new_map(int_map)) != NULL);
  assert(bunny_map_set_data(map, 1, &value, int*) == &value);
  bunny_malloc_failure(true);
  assert(bunny_map_set_data(map, 2, &value, int*) == NULL);
  bunny_malloc_failure(false);
  assert(bunny_map_size(map) == 1);
  assert(bunny_map_get_data(map, 1, int*) == &value);
  assert(bunny_map_get_data(map, 2, int*) == NULL);
  assert(bunny_delete_map(map) == 1);
}

int			main(void)
{
  test_empty_map_does_not_create_on_get();
  test_int_map_set_get_replace_iterate_and_clear();
  test_fast_foreach();
  test_allocation_failure();
  return (EXIT_SUCCESS);
}
