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

static void		backadd(void)
{
  t_bunny_list		*lst;
  t_bunny_node		*nod;
  size_t		cnt;

  lst = bunny_new_list();
  assert(bunny_list_empty(lst));

  for (cnt = 0; cnt < 20; ++cnt)
    {
      assert(bunny_list_push_back(lst, cnt));
      assert(bunny_list_size(lst) == cnt + 1);
    }

  for (cnt = 0, nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod), ++cnt)
    assert(bunny_list_data(nod, size_t) == cnt);

  for (cnt = bunny_list_size(lst) - 1, nod = bunny_list_end(lst);
       nod != NULL; nod = bunny_list_prev(nod), --cnt)
    assert(bunny_list_data(nod, size_t) == cnt);

  // Remove 5 first and 5 back

  for (cnt = 0; cnt < 5; ++cnt)
    {
      bunny_list_pop_front(lst, size_t);
      bunny_list_pop_back(lst, size_t);
    }
  for (cnt = 5, nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod), ++cnt)
    assert(bunny_list_data(nod, size_t) == cnt);

  assert(bunny_list_front(lst, size_t) == 5);
  assert(bunny_list_back(lst, size_t) == 14);
  assert(bunny_list_size(lst) == 10);

  bunny_delete_list(lst);
}

static void		frontadd(void)
{
  t_bunny_list		*lst;
  t_bunny_node		*nod;
  ssize_t		cnt;

  lst = bunny_new_list();
  assert(bunny_list_empty(lst));

  for (cnt = 19; cnt >= 0; --cnt)
    {
      assert(bunny_list_push_front(lst, cnt));
      assert(bunny_list_size(lst) == (size_t)(20 - cnt));
    }

  for (cnt = 0, nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod), ++cnt)
    assert(bunny_list_data(nod, ssize_t) == cnt);

  for (cnt = bunny_list_size(lst) - 1, nod = bunny_list_end(lst);
       nod != NULL; nod = bunny_list_prev(nod), --cnt)
    assert(bunny_list_data(nod, ssize_t) == cnt);

  // Remove 5 first and 5 back
  
  for (cnt = 0; cnt < 5; ++cnt)
    {
      bunny_list_pop_back(lst, size_t);
      bunny_list_pop_front(lst, size_t);
    }
  for (cnt = 5, nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod), ++cnt)
    assert(bunny_list_data(nod, ssize_t) == cnt);

  assert(bunny_list_front(lst, ssize_t) == 5);
  assert(bunny_list_back(lst, ssize_t) == 14);
  assert(bunny_list_size(lst) == 10);

  bunny_delete_list(lst);
}

static bool		only_greater_than(const void	*data,
					  void		*param)
{
  size_t		lim = (size_t)param;
  size_t		val = (size_t)data;

  return (val > lim);
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

static char		*randstring(void)
{
  char			buffer[16];
  size_t		i;

  for (i = 0; i < 15; ++i)
    buffer[i] = 'a' + rand() % ('z' - 'a');
  buffer[i] = '\0';
  return (strdup(&buffer[0]));
}

static void		filter_and_sort_and_serialize(void)
{
  t_bunny_list		*lst;
  t_bunny_list		*fil;
  t_bunny_node		*nod;
  t_bunny_vector	*vec;
  size_t		i;

  lst = bunny_new_list();
  assert(bunny_list_empty(lst));

  // Fill with random numbers

  for (i = 0; i < 300; ++i)
    bunny_list_push_back(lst, (size_t)rand() % 300);

  // Create a sublist of specific nodes and test it

  assert(fil = bunny_list_filter(lst, only_greater_than, (void*)150));

  bunny_delete_list(lst);

  for (nod = bunny_list_begin(fil); nod != NULL; nod = bunny_list_next(nod))
    assert(bunny_list_data(nod, size_t) > 150);

  // Sort the sublist and test it

  bunny_list_sort(fil, sort_int, NULL);

  for (nod = bunny_list_begin(fil); nod != NULL && nod->next != NULL; nod = bunny_list_next(nod))
    {
      assert(bunny_list_data(nod, size_t) <= bunny_list_data(nod->next, size_t));
      bunny_list_data(nod, char*) = randstring();
    }
  if (nod)
    bunny_list_data(nod, char*) = randstring();

  // Transform the list into a vector

  assert(vec = bunny_list_tie(fil, size_t));

  for (nod = bunny_list_begin(fil), i = 0; nod != NULL && nod->next != NULL; nod = bunny_list_next(nod), ++i)
    {
      assert(bunny_list_data(nod, char*) == bunny_vector_data(vec, i, char*));
      free(bunny_list_data(nod, char*));
    }
  if (nod)
    free(bunny_list_data(nod, char*));

  bunny_delete_list(fil);
  bunny_delete_vector(vec);
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  srand(time(NULL));
  backadd();
  frontadd();
  filter_and_sort_and_serialize();
  return (EXIT_SUCCESS);
}

