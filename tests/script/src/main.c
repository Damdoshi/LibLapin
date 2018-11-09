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
  /* */
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", a);

  bunny_save_configuration(BC_DABSIC, "tmp.dab", a);
  assert(b = bunny_load_configuration(BC_DABSIC, "./tmp.dab", NULL));
  bunny_save_configuration(BC_DABSIC, "tmp2.dab", b);
  assert(system("diff tmp.dab tmp2.dab") == 0);
  system("rm tmp*.dab");
  /* */
  printf("\n--------------- test %s execution --------------\n", str);

  if (strcmp(str, "env.dab") == 0)
    {
      bunny_configuration_create_mode(true);
      assert(bunny_configuration_setf(a, 42, "DynamicValue"));
      bunny_save_configuration(BC_DABSIC, "/dev/stdout", a);
    }

  t_bunny_configuration	*mainf = bunny_configuration_go_get_node(a, "main");
  const char		*res;

  if (!mainf)
    printf("No main found!\n");
  else
    assert(bunny_configuration_execute(mainf, false, NULL));

  assert(bunny_configuration_get_string(mainf, &res));
  printf("Computed result is: %s.\n", res);

  printf("\n");
  bunny_delete_configuration(a);
  //bunny_delete_configuration(b);
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  srand(time(NULL));
  bunny_set_error_descriptor(2);
  bunny_set_log_filter("syntax");
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  refresh_test("address.dab");
  refresh_test("select.dab");
  refresh_test("simple_loop_call.dab");
  refresh_test("factoriel.dab");
  refresh_test("with.dab");
  refresh_test("character.dab");
  refresh_test("fibo.dab");
  refresh_test("getretval.dab");
  refresh_test("factoriel.dab");
  refresh_test("doublefunc.dab");
  refresh_test("return.dab");
  refresh_test("classic_func_call.dab");
  refresh_test("named_func_call.dab");
  refresh_test("simple_cast.dab");
  refresh_test("operation_cast.dab");
  refresh_test("complex_cast.dab");
  refresh_test("assign_cascade.dab");
  refresh_test("env.dab");

  return (EXIT_SUCCESS);
}
