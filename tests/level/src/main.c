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
  (void)argv;
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);
  int			i;

  for (i = 1; i < 10; ++i)
    printf("level %d: %d.\n", i, bunny_next_level_experience(i) * 1000);

  assert(bunny_next_level_experience(1) * 1000 == 1000);
  assert(bunny_next_level_experience(2) * 1000 == 3000);
  assert(bunny_next_level_experience(3) * 1000 == 6000);
  assert(bunny_next_level_experience(4) * 1000 == 10000);
  assert(bunny_next_level_experience(5) * 1000 == 15000);

  return (EXIT_SUCCESS);
}
