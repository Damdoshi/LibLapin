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
  t_bunny_bitfield	*bf;
  size_t		i;
  
  assert(bf = bunny_new_bitfield(4096));
  for (i = 0; i < 4096; ++i)
    bunny_bitfield_set(bf, i);
  for (i = 0; i < 4096; ++i)
    assert(bunny_bitfield_get(bf, i));

  for (i = 0; i < 4096; i += 2)
    bunny_bitfield_clr(bf, i);

  for (i = 0; i < 4096; ++i)
    if (i % 2)
      assert(bunny_bitfield_get(bf, i));
    else
      assert(bunny_bitfield_get(bf, i) == false);

  bunny_delete_bitfield(bf);
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

