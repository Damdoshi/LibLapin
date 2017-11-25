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

  if ((a = bunny_load_configuration(BC_DABSIC, str, NULL)) == NULL)
    {
      bunny_perror(NULL);
      exit(EXIT_FAILURE);
    }

  bunny_save_configuration(BC_DABSIC, "/dev/stdout", a);

  bunny_save_configuration(BC_DABSIC, "tmp.dab", a);
  assert(b = bunny_load_configuration(BC_DABSIC, "./tmp.dab", NULL));
  bunny_save_configuration(BC_DABSIC, "tmp2.dab", b);
  assert(system("diff tmp.dab tmp2.dab") == 0);
  system("rm tmp*.dab");

  bunny_delete_configuration(a);
  bunny_delete_configuration(b);
}

int			main(int		argc,
			     char		**argv)
{
  t_bunny_configuration	*triple;
  int			val;

  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  bunny_set_error_descriptor(2);
  if (argc >= 2)
    {
      if (argc == 3)
	refresh_test(argv[1]);
      else
	alarm(2);
      return (EXIT_SUCCESS);
    }
  refresh_test("fields.dab");
  refresh_test("scopes.dab");
  refresh_test("arrays.dab");
  refresh_test("complex.dab");

  refresh_test("./triple.dab");

  printf("--------------- manual test triple.dab --------------\n");

  assert(triple = bunny_load_configuration(BC_DABSIC, "triple.dab", NULL));
  assert(bunny_configuration_go_get(triple, &val, "SAV"));
  assert(val == 42);
  assert(bunny_configuration_go_get(triple, &val, "SAV[0]"));
  assert(val == 1);
  assert(bunny_configuration_go_get(triple, &val, "SAV[1]"));
  assert(val == 2);
  assert(bunny_configuration_go_get(triple, &val, "SAV[2]"));
  assert(val == 3);
  assert(bunny_configuration_go_get(triple, &val, "SAV.A"));
  assert(val == 4);
  assert(bunny_configuration_go_get(triple, &val, "SAV.B"));
  assert(val == 5);
  assert(bunny_configuration_go_get(triple, &val, "SAV.C"));
  assert(val == 6);
  bunny_delete_configuration(triple);

  refresh_test("./parameters.dab");
  refresh_test("./multi.dab");
  refresh_test("./with_xml.dab");
  refresh_test("./with_csv.dab");
  refresh_test("./sequence.dab");

  return (EXIT_SUCCESS);
}
