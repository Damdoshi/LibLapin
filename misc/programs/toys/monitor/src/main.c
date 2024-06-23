/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<unistd.h>
#include		<fcntl.h>
#include		<string.h>
#include		<stdio.h>
#include		<time.h>
#include		<signal.h>
#include		<assert.h>
#include		<stdlib.h>
#include		<lapin.h>

double			gl_obal = 4.2;

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

int			main(int		argc,
			     char		**argv)
{
  int			i, j;

  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  bunny_add_monitored_value("main.i", &i);
  bunny_add_monitored_value("main.j", &j);
  bunny_add_monitored_value("gl_obal", &gl_obal);
  bunny_add_monitored_value("string", "I am fine!");
  bunny_add_monitored_value("stringx", "I am fine!");

  bunny_remove_monitored_value("stringx");

  puts("--- First ---");
  i = 5;
  j = 7;
  bunny_print_monitored_value(1, NULL);

  puts("--- Second ---");
  i = 10;
  j = 15;
  gl_obal = 10.5;
  bunny_print_monitored_value(1, NULL);

  puts("--- Third ---");
  i = 30;
  j = 0;
  gl_obal = 0.33;
  bunny_print_monitored_value(1, "main.*");

  return (EXIT_SUCCESS);
}

