/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<string.h>
#include		<stdio.h>
#include		<time.h>
#include		<signal.h>
#include		<assert.h>
#include		<stdlib.h>
#include		<lapin.h>

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

static int		sort_int(const void		*a,
				 const void		*b,
				 void			*param)
{
  size_t		x = (size_t)a;
  size_t		y = (size_t)b;

  (void)param;
  return (x - y);
}

static void		test(void)
{
  t_bunny_vector	*vector;
  t_bunny_node		*node;
  t_bunny_list		*list;
  size_t		i;

  assert(vector = bunny_new_vector(50, size_t));
  assert(!bunny_vector_empty(vector));
  assert(bunny_vector_size(vector) == 50);
  assert(bunny_vector_elem_size(vector) == sizeof(size_t));

  for (i = 0; i < bunny_vector_size(vector); ++i)
    bunny_vector_data(vector, i, size_t) = i * i;

  assert(vector = bunny_vector_resize(vector, 100));

  for (i = 0; i < 50; ++i)
    assert(bunny_vector_data(vector, i, size_t) == i * i);

  for (i = 50; i < bunny_vector_size(vector); ++i)
    bunny_vector_data(vector, i, size_t) = (99 - i) * (99 - i);

  //

  bunny_vector_sort(vector, sort_int, NULL);

  for (i = 0; i < bunny_vector_size(vector) - 1; ++i)
    assert(bunny_vector_data(vector, i, size_t) <= bunny_vector_data(vector, i + 1, size_t));

  assert(vector = bunny_vector_resize(vector, 50));
  assert(vector = bunny_vector_crop(vector));

  assert(list = bunny_vector_untie(vector));

  for (node = bunny_list_begin(list), i = 0; node != NULL && i < bunny_vector_size(vector);
       ++i, node = bunny_list_next(node))
    {
      assert(bunny_vector_data(vector, i, size_t) == *bunny_list_data(node, size_t*));
      free(bunny_list_data(node, size_t*));
    }

  bunny_delete_list(list);
  bunny_delete_vector(vector);
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  test();
  return (EXIT_SUCCESS);
}

