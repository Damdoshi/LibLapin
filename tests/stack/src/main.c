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
  size_t		cnt, prev;

  (void)argv;
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  cnt = 0;
  srand(time(NULL));
  for (i = 0; i < 3; ++i)
    {
      t_bunny_stack	*stack = bunny_new_stack();

      prev = 0;
      assert(bunny_stack_empty(stack));
      for (j = 0; j < 3; ++j)
	{
	  printf("-- Go up --\n");
	  l = rand() % 30 + 10;
	  for (k = 0; k < l; ++k)
	    {
	      printf("%zu\n", cnt);
	      if (bunny_stack_push(stack, cnt) == false)
		return (EXIT_FAILURE);
	      assert(bunny_stack_top(stack, void*) == (void*)cnt);
	      cnt += 1;
	    }
	  assert(bunny_stack_size(stack) == l + prev);

	  printf("-- Go down --\n");

	  m = rand() % l;
	  for (k = 0; k < m; ++k)
	    {
	      cnt -= 1;
	      printf("%zu\n", cnt);
	      assert(bunny_stack_top(stack, void*) == (void*)cnt);
	      bunny_stack_pop(stack, void*);
	    }

	  assert(bunny_stack_size(stack) == l - m + prev);

	  prev = bunny_stack_size(stack);
	}

      bunny_delete_stack(stack);
    }
  return (EXIT_SUCCESS);
}
