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

  if ((a = bunny_load_configuration(BC_XML, str, NULL)) == NULL)
    {
      bunny_perror(NULL);
      exit(EXIT_FAILURE);
    }
  
  bunny_save_configuration(BC_XML, "/dev/stdout", a);

  bunny_save_configuration(BC_XML, "tmp.xml", a);
  assert(b = bunny_load_configuration(BC_XML, "./tmp.xml", NULL));
  bunny_save_configuration(BC_XML, "tmp2.xml", b);
  assert(system("diff tmp.xml tmp2.xml") == 0);
  system("rm tmp*.xml");

  bunny_delete_configuration(a);
  bunny_delete_configuration(b);
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  refresh_test("markup.xml");
  refresh_test("properties.xml");
  refresh_test("markup_value.xml");
  refresh_test("include.xml");

  return (EXIT_SUCCESS);
}

