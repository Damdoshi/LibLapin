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

  if ((a = bunny_load_configuration(BC_LISP, str, NULL)) == NULL)
    {
      bunny_perror(NULL);
      exit(EXIT_FAILURE);
    }

  bunny_save_configuration(BC_LISP, "/dev/stdout", a);

  bunny_save_configuration(BC_LISP, "tmp.lisp", a);
  assert(b = bunny_load_configuration(BC_LISP, "./tmp.lisp", NULL));
  bunny_save_configuration(BC_LISP, "tmp2.lisp", b);
  assert(system("diff tmp.lisp tmp2.lisp") == 0);
  system("rm tmp*.lisp");

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

  refresh_test("inside_list.lisp");
  refresh_test("list.lisp");

  return (EXIT_SUCCESS);
}
