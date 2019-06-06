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
  ssize_t		i, j, k, l;

  len = rand() % 4000 + 2000;

  void			**id = bunny_alloca(sizeof(*id) * len);

  pool = bunny_new_pool(len, size_t);
  bunny_delete_pool(pool);
  pool = bunny_new_pool(len, size_t);

  for (i = 0; i < len; ++i)
    {
      assert(id[i] = bunny_pool_new(pool, size_t));
      *(size_t*)id[i] = 42;
    }

  for (i = 0; i < len; ++i)
    {
      assert(*(size_t*)id[0] == 42);
      bunny_pool_free(pool, id[0]);
    }
  assert(pool->nmemb - pool->nbr_occupied == (size_t)len);

  for (i = 0; i < len / 2; ++i)
    assert(id[i] = bunny_pool_new(pool, size_t));
  for (i = len / 2 - 1; i >= 0; --i)
    bunny_pool_free(pool, id[i]);

  for (i = 0; i < 100; ++i)
    {
      j = rand() % (int)(len / 1.5);
      for (k = 0; k < j; ++k)
	bunny_pool_new(pool, size_t);
      j = rand() % (len / 2);
      for (k = 0; k < j && bunny_pool_size(pool) > 0; ++k)
	{
	  l = rand() % bunny_pool_size(pool);
	  assert(*(size_t*)pool->data[l] == 42);
	  bunny_pool_free(pool, pool->data[l]);
	}
    }

  bunny_delete_pool(pool);
  bunny_freea(id);
}

int			main(int		argc,
			     char		**argv)
{
  int			i;

  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  for (i = 0; i < 10; ++i)
    test();
  return (EXIT_SUCCESS);
}

