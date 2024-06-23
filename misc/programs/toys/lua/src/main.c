/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<time.h>
#include		<stdlib.h>
#include		<signal.h>
#include		<assert.h>
#include		<lapin.h>

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

void			refresh_test(const char	*str)
{
  t_bunny_configuration	*a, *b;

  printf("--------------- test %s --------------\n", str);

  if ((a = bunny_load_configuration(BC_LUA, str, NULL)) == NULL)
    {
      bunny_perror(NULL);
      exit(EXIT_FAILURE);
    }

  bunny_save_configuration(BC_LUA, "/dev/stdout", a);

  bunny_save_configuration(BC_LUA, "tmp.lua", a);
  assert(b = bunny_load_configuration(BC_LUA, "./tmp.lua", NULL));
  bunny_save_configuration(BC_LUA, "tmp2.lua", b);
  assert(system("diff tmp.lua tmp2.lua") == 0);
  system("rm tmp*.lua");

  bunny_delete_configuration(a);
  bunny_delete_configuration(b);
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  srand(time(NULL));
  bunny_set_error_descriptor(2);
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  refresh_test("fields.lua");
  refresh_test("scopes.lua");
  refresh_test("arrays.lua");

  return (EXIT_SUCCESS);
}
