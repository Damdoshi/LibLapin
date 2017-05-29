/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

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

int			main(int		argc,
			     char		**argv)
{
  size_t		i, j, k, l, m;
  size_t		add, rem, prev;

  (void)argv;
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  srand(time(NULL));
  for (i = 0; i < 3; ++i)
    {
      t_bunny_queue	*queue = bunny_new_queue();

      add = 0;
      rem = 0;
      prev = 0;
      assert(bunny_queue_empty(queue));
      for (j = 0; j < 3; ++j)
	{
	  printf("-- Fill --\n");

	  l = rand() % 30 + 10;
	  for (k = 0; k < l; ++k)
	    {
	      if (bunny_queue_push(queue, add) == false)
		return (EXIT_FAILURE);
	      printf("%zu\n", add);
	      assert(bunny_queue_front(queue, void*) == (void*)rem);
	      add += 1;
	    }
	  assert(bunny_queue_size(queue) == l + prev);

	  printf("-- Empty --\n");

	  m = rand() % l;
	  for (k = 0; k < m; ++k)
	    {
	      assert(bunny_queue_front(queue, void*) == (void*)rem);
	      printf("%zu\n", rem);
	      bunny_queue_pop(queue, void*);
	      rem += 1;
	    }

	  assert(bunny_queue_size(queue) == l - m + prev);

	  prev = bunny_queue_size(queue);
	}

      bunny_delete_queue(queue);
    }
  return (EXIT_SUCCESS);
}
