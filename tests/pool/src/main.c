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

static void		test(void)
{
  t_bunny_pool		*pool;
  ssize_t		len;
  ssize_t		i;

  len = rand() % 80 + 20;
  
  size_t		*id = alloca(sizeof(*id) * len);
  size_t		x;

  pool = bunny_new_pool(len, size_t);

  for (i = 0; i < len; ++i)
    assert(bunny_pool_get(pool, &id[i], size_t));

  x = 42;

  assert(bunny_pool_get(pool, &x, size_t) == NULL);
  assert(bunny_pool_get(pool, &x, size_t) == NULL);
  assert(bunny_pool_get(pool, &x, size_t) == NULL);
  assert(x == 42);

  for (i = 0; i < len; ++i)
    {
      assert(bunny_pool_free_elem(pool) == (size_t)i);
      bunny_pool_release(pool, id[i]);
    }
  assert(bunny_pool_free_elem(pool) == (size_t)i);

  for (i = 0; i < len / 2; ++i)
    assert(bunny_pool_get(pool, &id[i], size_t));

  for (i = len / 2 - 1; i >= 0; --i)
    bunny_pool_release(pool, id[i]);

  bunny_delete_pool(pool);
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

