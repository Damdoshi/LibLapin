// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#if			!(_WIN32 || __WIN32__ || __APPLE__)
# include		<sys/wait.h>
#endif
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
#if			!(_WIN32 || __WIN32__ || __APPLE__)
  sighandler_t		handler;
  int			status;
  int			*ptr = &subproc->_stdin;
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
	  scream_log_if("%p subprocess, %d delay -> %d", "unix", subproc, delay, status);
	  return (status);
	}
      signal(SIGALRM, handler);
      bunny_usleep(delay * 1e6);
    }
  kill(subproc->pid, SIGINT);
  scream_log_if("%p subprocess, %d delay -> %d (Killed)", "unix", subproc, delay, 0);
  return (0);
#else
  return (-1);
#endif
}

