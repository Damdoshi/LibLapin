/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
** EFRITS 2022-2024
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#include		"lapin.h"

static bool		filter(const void		*lst,
			       void			*param)
{
  const int		*ptr = lst;

  assert(param == (void*)0x42);
  return (*ptr > 2 && *ptr < 5);
}

static int		comparator(const void		*a,
				   const void		*b,
				   void			*param)
{
  assert(param == (void*)0x84);
  return (*(int*)a - *(int*)b);
}

static void		increment(void			*node,
				  void			*param)
{
  assert(param == (void*)0x20);
  *(int*)node += 1;
}

int			main(void)
{
  t_bunny_list		*lst, *filtered;
  int			elm[5] = {6, 5, 4, 3, 2};
  t_bunny_threadpool	*pool;
  t_bunny_vector	*vector;

  // Utilisation en pile avant
  assert((lst = bunny_new_list()) != NULL);
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == NULL);

  assert(bunny_list_push_front(lst, &elm[0]));
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[0]);

  assert(bunny_list_push_front(lst, &elm[1]));
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[1]);

  assert(bunny_list_push_front(lst, &elm[2]));
  assert(bunny_list_size(lst) == 3);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[2]);

  assert(bunny_list_pop_front(lst, int*) == &elm[2]);
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[1]);

  assert(bunny_list_pop_front(lst, int*) == &elm[1]);
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[0]);

  assert(bunny_list_pop_front(lst, int*) == &elm[0]);
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == NULL);
  assert(bunny_list_pop_back(lst, int*) == NULL);

  assert(bunny_list_push_front(lst, &elm[0]));
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[0]);

  assert(bunny_list_push_front(lst, &elm[1]));
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[1]);

  bunny_malloc_failure(true);
  assert(bunny_list_push_front(lst, &elm[0]) == false);
  bunny_malloc_failure(false);

  assert(bunny_delete_list(lst) == 2);

  // Utilisation en file
  assert((lst = bunny_new_list()) != NULL);
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == NULL);

  assert(bunny_list_push_back(lst, &elm[0]));
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[0]);

  assert(bunny_list_push_back(lst, &elm[1]));
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[0]);

  assert(bunny_list_push_back(lst, &elm[2]));
  assert(bunny_list_size(lst) == 3);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[0]);

  assert(bunny_list_pop_front(lst, int*) == &elm[0]);
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[1]);

  assert(bunny_list_pop_front(lst, int*) == &elm[1]);
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[2]);

  assert(bunny_list_pop_front(lst, int*) == &elm[2]);
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == NULL);
  assert(bunny_list_pop_front(lst, int*) == NULL);

  assert(bunny_list_push_back(lst, &elm[0]));
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[0]);

  assert(bunny_list_push_back(lst, &elm[1]));
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_front(lst, int*) == &elm[0]);

  bunny_malloc_failure(true);
  assert(bunny_list_push_back(lst, &elm[0]) == false);
  bunny_malloc_failure(false);

  assert(bunny_delete_list(lst) == 2);

  // Utilisation en pile arrière
  assert((lst = bunny_new_list()) != NULL);
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == NULL);

  assert(bunny_list_push_back(lst, &elm[0]));
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[0]);

  assert(bunny_list_push_back(lst, &elm[1]));
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[1]);

  assert(bunny_list_push_back(lst, &elm[2]));
  assert(bunny_list_size(lst) == 3);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[2]);

  assert(bunny_list_pop_back(lst, int*) == &elm[2]);
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[1]);

  assert(bunny_list_pop_back(lst, int*) == &elm[1]);
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[0]);

  assert(bunny_list_pop_back(lst, int*) == &elm[0]);
  assert(bunny_list_size(lst) == 0);
  assert(bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == NULL);
  assert(bunny_list_pop_back(lst, int*) == NULL);

  assert(bunny_list_push_back(lst, &elm[0]));
  assert(bunny_list_size(lst) == 1);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[0]);

  assert(bunny_list_push_back(lst, &elm[1]));
  assert(bunny_list_size(lst) == 2);
  assert(!bunny_list_empty(lst));
  assert(bunny_list_back(lst, int*) == &elm[1]);

  bunny_malloc_failure(true);
  assert(bunny_list_push_back(lst, &elm[0]) == false);
  bunny_malloc_failure(false);

  assert(bunny_delete_list(lst) == 2);

  // Utils
  bunny_malloc_failure(true);
  assert(bunny_list_filter(NULL, NULL, NULL) == NULL);
  bunny_malloc_failure(false);
  assert((lst = bunny_new_list()) != NULL);
  assert(bunny_list_push_back(lst, &elm[0]));
  assert(bunny_list_push_back(lst, &elm[1]));
  assert(bunny_list_push_back(lst, &elm[2]));
  assert(bunny_list_push_back(lst, &elm[3]));
  assert(bunny_list_push_back(lst, &elm[4]));
  assert((filtered = bunny_list_filter(lst, filter, (void*)0x42)));
  assert(bunny_list_front(filtered, int*) == &elm[2]);
  assert(bunny_list_back(filtered, int*) == &elm[3]);
  bunny_list_sort(filtered, comparator, (void*)0x84);
  assert(bunny_list_front(filtered, int*) == &elm[3]);
  assert(bunny_list_back(filtered, int*) == &elm[2]);

  assert(*bunny_list_front(filtered, int*) == 3);
  assert(*bunny_list_back(filtered, int*) == 4);
  bunny_list_foreach(filtered, increment, (void*)0x20);
  assert(bunny_list_front(filtered, int*) == &elm[3]);
  assert(bunny_list_back(filtered, int*) == &elm[2]);
  assert(*bunny_list_front(filtered, int*) == 4);
  assert(*bunny_list_back(filtered, int*) == 5);

  assert((pool = bunny_new_threadpool(3)));
  bunny_list_fast_foreach(pool, filtered, increment, (void*)0x20);
  assert(bunny_list_front(filtered, int*) == &elm[3]);
  assert(bunny_list_back(filtered, int*) == &elm[2]);
  assert(*bunny_list_front(filtered, int*) == 5);
  assert(*bunny_list_back(filtered, int*) == 6);
  // bunny_delete_threadpool(pool);

  bunny_malloc_failure(true);
  assert((vector = bunny_list_tie(lst, int)) == NULL);
  bunny_malloc_failure(false);

  assert((vector = bunny_list_tie(lst, int)));
  for (size_t i = 0; i < NBRCELL(elm); ++i)
    assert(bunny_vector_data(vector, i, int) == elm[i]);
  bunny_delete_vector(vector);

  return (EXIT_SUCCESS);
}
