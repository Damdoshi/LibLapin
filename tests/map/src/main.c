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

static int		testint(const void	*a,
				const void	*b,
				void		*c)
{
  int			ka = (ssize_t)a;
  int			kb = (ssize_t)b;

  assert(c == (void*)0x1);
  return (ka - kb);
}

static void		*dupint(const void	*a,
				void		*b)
{
  assert(b == (void*)0x1);
  return ((void*)a);
}

static void		delint(void		*a,
			       void		*b)
{
  (void)a;
  assert(b == (void*)0x1);
}

static void		check_order(t_bunny_map	*nod,
				    void	*param)
{
  static ssize_t	previous;
  ssize_t		current = (ssize_t)nod->data;

  if (param != NULL)
    previous = 0;
  else
    {
      assert(previous <= current);
      previous = current;
    }
}

static void		test(void)
{
  static t_bunny_map	empty;
  ssize_t		rnd[4096];
  t_bunny_map		*map;
  ssize_t		val;
  size_t		i;

  assert(map = bunny_new_map(testint, dupint, delint, (void*)0x1));

  for (i = 0; i < sizeof(rnd) / sizeof(rnd[i]); ++i)
    {
      rnd[i] = rand() % 2000000000;
      bunny_map_set_data(map, rnd[i], rnd[i], ssize_t);
    }

  // Some values may be repeated so bunny_map_size may not be as big as the size
  // of the array... So here is a little margin.
  assert(abs(bunny_map_size(map) - sizeof(rnd) / sizeof(rnd[0])) < 5);

  for (i = 0; i < 4096; ++i)
    {
      val = rnd[rand() % (sizeof(rnd) / sizeof(rnd[i]))];
      assert(bunny_map_get_data(map, val, ssize_t) == val);
    }

  assert(bunny_map_get_data(map, 3000, ssize_t) == 0);
  assert(bunny_map_get_data(map, 4000, ssize_t) == 0);
  assert(bunny_map_get_data(map, 5000, ssize_t) == 0);
  assert(bunny_map_get_data(map, 6000, ssize_t) == 0);

  check_order(&empty, (void*)0x1);
  bunny_map_foreach(map, check_order, NULL);

  bunny_delete_map(map);
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

