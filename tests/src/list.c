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

static bool		between_three_and_five(const void	*data,
					       void		*param)
{
  assert(param == (void*)0x4242);
  return (*(const int*)data >= 3 && *(const int*)data <= 5);
}

static int		compare_int_ptrs(const void		*a,
					 const void		*b,
					 void			*param)
{
  assert(param == (void*)0x8484);
  return (*(const int*)a - *(const int*)b);
}

static void		increment_int(void			*data,
				      void			*param)
{
  assert(param == (void*)0x2020);
  *(int*)data += 1;
}

static void		free_list_payloads(t_bunny_list		*lst)
{
  t_bunny_node		*nod;

  for (bunny_list_all(lst, nod))
    bunny_free(bunny_list_data(nod, void*));
}

static void		test_empty_list(void)
{
  t_bunny_list		*lst;

  assert((lst = bunny_new_list()) != NULL);
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == NULL);
  assert(bunny_list_back(lst, int*) == NULL);
  assert(bunny_list_begin(lst) == NULL);
  assert(bunny_list_end(lst) == NULL);
  assert(bunny_list_pop_front(lst, int*) == NULL);
  assert(bunny_list_pop_back(lst, int*) == NULL);
  assert(bunny_delete_list(lst) == 0);
}

static void		test_push_front_and_pop_front(void)
{
  t_bunny_list		*lst;
  int			elm[5] = {0, 1, 2, 3, 4};
  size_t		i;

  assert((lst = bunny_new_list()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    {
      assert(bunny_list_push_front(lst, &elm[i]));
      assert(bunny_list_size(lst) == i + 1);
      assert(bunny_list_front(lst, int*) == &elm[i]);
      assert(bunny_list_back(lst, int*) == &elm[0]);
    }
  for (i = NBRCELL(elm); i > 0; --i)
    assert(bunny_list_pop_front(lst, int*) == &elm[i - 1]);
  assert(bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == NULL);
  assert(bunny_list_back(lst, int*) == NULL);
  assert(bunny_delete_list(lst) == 0);
}

static void		test_push_back_and_pop_back(void)
{
  t_bunny_list		*lst;
  int			elm[5] = {0, 1, 2, 3, 4};
  size_t		i;

  assert((lst = bunny_new_list()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    {
      assert(bunny_list_push_back(lst, &elm[i]));
      assert(bunny_list_size(lst) == i + 1);
      assert(bunny_list_front(lst, int*) == &elm[0]);
      assert(bunny_list_back(lst, int*) == &elm[i]);
    }
  for (i = NBRCELL(elm); i > 0; --i)
    assert(bunny_list_pop_back(lst, int*) == &elm[i - 1]);
  assert(bunny_list_empty(lst));
  assert(bunny_delete_list(lst) == 0);
}

static void		test_push_back_and_pop_front_fifo(void)
{
  t_bunny_list		*lst;
  int			elm[5] = {10, 11, 12, 13, 14};
  size_t		i;

  assert((lst = bunny_new_list()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    assert(bunny_list_push_back(lst, &elm[i]));
  for (i = 0; i < NBRCELL(elm); ++i)
    assert(bunny_list_pop_front(lst, int*) == &elm[i]);
  assert(bunny_list_empty(lst));
  assert(bunny_delete_list(lst) == 0);
}

static void		test_iterators_and_clear(void)
{
  t_bunny_list		*lst;
  t_bunny_node		*nod;
  int			elm[4] = {2, 4, 6, 8};
  int			expected_forward[4] = {2, 4, 6, 8};
  int			expected_reverse[4] = {8, 6, 4, 2};
  size_t		i;

  assert((lst = bunny_new_list()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    assert(bunny_list_push_back(lst, &elm[i]));
  i = 0;
  for (bunny_list_all(lst, nod))
    {
      assert(*bunny_list_data(nod, int*) == expected_forward[i]);
      ++i;
    }
  assert(i == NBRCELL(expected_forward));
  i = 0;
  for (bunny_list_all_rev(lst, nod))
    {
      assert(*bunny_list_data(nod, int*) == expected_reverse[i]);
      ++i;
    }
  assert(i == NBRCELL(expected_reverse));
  bunny_list_clear(lst);
  assert(bunny_list_empty(lst));
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_begin(lst) == NULL);
  assert(bunny_list_end(lst) == NULL);
  assert(bunny_delete_list(lst) == 0);
}

static void		test_filter_sort_foreach_and_fast_foreach(void)
{
  t_bunny_list		*lst;
  t_bunny_list		*filtered;
  t_bunny_threadpool	*pool;
  int			elm[6] = {6, 1, 5, 2, 4, 3};
  size_t		i;

  assert((lst = bunny_new_list()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    assert(bunny_list_push_back(lst, &elm[i]));
  assert((filtered = bunny_list_filter(lst, between_three_and_five, (void*)0x4242)) != NULL);
  assert(bunny_list_size(filtered) == 3);
  bunny_list_sort(filtered, compare_int_ptrs, (void*)0x8484);
  assert(*bunny_list_pop_front(filtered, int*) == 3);
  assert(*bunny_list_pop_front(filtered, int*) == 4);
  assert(*bunny_list_pop_front(filtered, int*) == 5);
  assert(bunny_list_empty(filtered));
  assert(bunny_delete_list(filtered) == 0);

  assert((filtered = bunny_list_filter(lst, between_three_and_five, (void*)0x4242)) != NULL);
  bunny_list_foreach(filtered, increment_int, (void*)0x2020);
  assert(elm[2] == 6);
  assert(elm[4] == 5);
  assert(elm[5] == 4);
  assert((pool = bunny_new_threadpool(2)) != NULL);
  assert(bunny_list_fast_foreach(pool, filtered, increment_int, (void*)0x2020));
  bunny_delete_threadpool(pool);
  assert(elm[2] == 7);
  assert(elm[4] == 6);
  assert(elm[5] == 5);
  assert(bunny_delete_list(filtered) == 3);
  assert(bunny_delete_list(lst) == NBRCELL(elm));
}

static void		test_list_tie_copies_values(void)
{
  t_bunny_list		*lst;
  t_bunny_vector	*vec;
  int			elm[4] = {9, 8, 7, 6};
  size_t		i;

  assert((lst = bunny_new_list()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    assert(bunny_list_push_back(lst, &elm[i]));
  assert((vec = bunny_list_tie(lst, int)) != NULL);
  assert(bunny_vector_size(vec) == NBRCELL(elm));
  for (i = 0; i < NBRCELL(elm); ++i)
    assert(bunny_vector_data(vec, i, int) == elm[i]);
  elm[0] = 42;
  assert(bunny_vector_data(vec, 0, int) == 9);
  bunny_delete_vector(vec);
  assert(bunny_delete_list(lst) == NBRCELL(elm));
}

static void		test_allocation_failures(void)
{
  t_bunny_list		*lst;
  int			elm[2] = {1, 2};

  assert((lst = bunny_new_list()) != NULL);
  assert(bunny_list_push_back(lst, &elm[0]));
  bunny_malloc_failure(true);
  assert(bunny_list_push_front(lst, &elm[1]) == false);
  assert(bunny_list_push_back(lst, &elm[1]) == false);
  assert(bunny_list_filter(lst, between_three_and_five, (void*)0x4242) == NULL);
  assert(bunny_list_tie(lst, int) == NULL);
  bunny_malloc_failure(false);
  assert(bunny_list_size(lst) == 1);
  assert(bunny_list_pop_front(lst, int*) == &elm[0]);
  assert(bunny_delete_list(lst) == 0);
}

int			main(void)
{
  test_empty_list();
  test_push_front_and_pop_front();
  test_push_back_and_pop_back();
  test_push_back_and_pop_front_fifo();
  test_iterators_and_clear();
  test_filter_sort_foreach_and_fast_foreach();
  test_list_tie_copies_values();
  test_allocation_failures();
  return (EXIT_SUCCESS);
}
