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

static void		test(char		**env)
{
  static t_bunny_subprocess subproc;
  char			buffer[4096];
  size_t		len;

  subproc.stdout = 1;
  bunny_popen(&subproc, env, 3, "/bin/ls", "-l", "-a");
  len = read(subproc.stdout, &buffer[0], sizeof(buffer) - 1);
  buffer[len] = '\0';
  printf("Receive:\n%sEnd.\n", &buffer[0]);
  bunny_pclose(&subproc, 2);
}

int			main(int		argc,
			     char		**argv,
			     char		**env)
{
  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);
  test(env);
  return (EXIT_SUCCESS);
}

