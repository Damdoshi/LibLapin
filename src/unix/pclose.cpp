// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		<sys/wait.h>
#include		<stdlib.h>
#include		<signal.h>
#include		<unistd.h>
#include		"lapin_private.h"

static void		alarmhandler(int			x)
{
  (void)x;
}

int			bunny_pclose(t_bunny_subprocess		*subproc,
				     int			delay)
{
  sighandler_t		handler;
  int			status;
  int			*ptr = &subproc->stdin;
  int			i, l;

  for (i = 0, l = (sizeof(*subproc) - sizeof(subproc->pid)) / sizeof(*ptr); i < l; ++i)
    if (*ptr != -1)
      close(*ptr);
  if (delay)
    {
      handler = signal(SIGALRM, alarmhandler);
      alarm(delay);
      if (waitpid(subproc->pid, &status, 0) != -1)
	{
	  signal(SIGALRM, handler);
	  return (status);
	}
      signal(SIGALRM, handler);
    }
  kill(subproc->pid, SIGINT);
  return (0);
}

