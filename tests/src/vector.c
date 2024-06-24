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

static void		increment(void			*node,
				  void			*param)
{
  assert(param == (void*)0x20);
  *(int*)node += 1;
}

static int		intsort(const void	*a,
				const void	*b,
				void		*param)
{
  assert(param == (void*)0x84);
  return (*(int*)a - *(int*)b);
}

static bool		constructor(void	*_data,
				    void	*add)
{
  int			*data = _data;

  *data = 42;
  assert(add == (void*)0x42);
  return (true);
}

static bool		destructor(void		*data)
{
  int			*d = data;

  assert(*d > 0);
  return (true);
}

int			main(void)
{
  t_bunny_vector	*vec;

  assert((vec = bunny_build_vector(10, int, constructor, destructor, (void*)0x42)) != NULL);

  assert(!bunny_vector_empty(vec));
  assert(bunny_vector_size(vec) == 10);
  assert(bunny_vector_elem_size(vec) == sizeof(int));
  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    {
      assert(bunny_vector_data(vec, i, int) == 42);
      assert(*(int*)bunny_vector_address(vec, i) == 42);
      bunny_vector_data(vec, i, int) *= 2;
    }
  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, int) == 84);

  assert((vec = bunny_vector_resize(vec, 5, (void*)0x42)));
  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, int) == 84);

  assert((vec = bunny_vector_resize(vec, 10, (void*)0x42)));
  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    {
      if (i < 5)
	assert(bunny_vector_data(vec, i, int) == 84);
      else
	assert(bunny_vector_data(vec, i, int) == 42);
    }

  assert((vec = bunny_vector_crop(vec)));
  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    {
      if (i < 5)
	assert(bunny_vector_data(vec, i, int) == 84);
      else
	assert(bunny_vector_data(vec, i, int) == 42);
    }

  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    bunny_vector_data(vec, i, int) = bunny_vector_size(vec) - i;
  bunny_vector_sort(vec, intsort, (void*)0x84);
  for (size_t i = 0; i < bunny_vector_size(vec) - 1; ++i)
    assert(bunny_vector_data(vec, i, int) < bunny_vector_data(vec, i + 1, int));

  t_bunny_list		*lst;
  t_bunny_node		*node;

  assert((lst = bunny_vector_untie(vec)));
  assert((node = bunny_list_begin(lst)));
  assert(bunny_list_size(lst) == bunny_vector_size(vec));
  for (size_t i = 0; i < bunny_vector_size(vec) - 1; ++i)
    {
      assert(*bunny_list_data(node, int*) == bunny_vector_data(vec, i, int));
      node = bunny_list_next(node);
    }
  bunny_delete_list(lst);
  int			a = bunny_vector_data(vec, 0, int);

  bunny_vector_foreach(vec, increment, (void*)0x128);
  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, int) == a - 1 + (int)i);
  t_bunny_threadpool	*pool;

  assert((pool = bunny_new_threadpool(3)));
  bunny_vector_fast_foreach(pool, vec, increment, (void*)0x128);
  for (size_t i = 0; i < bunny_vector_size(vec); ++i)
    assert(bunny_vector_data(vec, i, int) == a - 2 + (int)i);

  bunny_delete_vector(vec);
}
