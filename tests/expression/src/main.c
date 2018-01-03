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

char *_bunny_write_expression_prec(const t_bunny_configuration *cnf);

void			refresh_test(const char	*str)
{
  t_bunny_configuration	*a, *b;

  printf("--------------- test %s --------------\n", str);

  if ((a = bunny_load_configuration(BC_DABSIC_EXPRESSION, str, NULL)) == NULL)
    {
      bunny_perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("------ complete %s ------\n", str);

  bunny_save_configuration(BC_DABSIC_EXPRESSION, "/dev/stdout", a);
  write(1, "\n", 1);

  printf("------ precomputed %s ------\n", str);

  char * x = _bunny_write_expression_prec(a);

  printf("%s\n", x);
  free(x);

  bunny_save_configuration(BC_DABSIC_EXPRESSION, "tmp.expr", a);
  assert(b = bunny_load_configuration(BC_DABSIC_EXPRESSION, "./tmp.expr", NULL));
  bunny_save_configuration(BC_DABSIC_EXPRESSION, "tmp2.expr", b);
  assert(system("diff tmp.expr tmp2.expr") == 0);
  system("rm tmp*.expr");

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

  refresh_test("simple.expr");
  refresh_test("very_simple.expr");
  refresh_test("single.expr");
  refresh_test("pow.expr");
  refresh_test("cat.expr");
  refresh_test("parenthesis.expr");
  refresh_test("arithmetic.expr");
  refresh_test("good_test.expr");
  refresh_test("bad_test.expr");
  refresh_test("big_operation.expr");
  refresh_test("ternary_true.expr");
  refresh_test("ternary_false.expr");
  refresh_test("lowbinary.expr");
  refresh_test("highbinary.expr");
  refresh_test("lshift.expr");
  refresh_test("rshift.expr");
  refresh_test("single_variable.expr");
  refresh_test("factorise.expr");
  refresh_test("assign.expr");

  return (EXIT_SUCCESS);
}

