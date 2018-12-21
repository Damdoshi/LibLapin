// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdlib.h>
#include		<unistd.h>
#include		<stdarg.h>
#include		"lapin_private.h"

static void		to_neg(int				*ptr,
			       size_t				len)
{
  size_t		i;

  for (i = 0; i < len; ++i)
    ptr[i] = -1;
}

#define			PATTERN		"%p subprocess, %p environment, %zu nbr_parameters, ... -> %d"

int			bunny_popen(t_bunny_subprocess		*subproc,
				    char			**env,
				    size_t			nbr,
				    ...)
{
#if			!(_WIN32 || __WIN32__)
  pid_t			pid;
  int			pip[7][2];
  int			*ptr = &subproc->_stdin;
  size_t		len = (sizeof(*subproc) - sizeof(subproc->pid)) / sizeof(subproc->_stdin);
  size_t		i;

  to_neg(&pip[0][0], sizeof(pip) / sizeof(pip[0][0]));
  for (i = 0; i < len; ++i)
    if (ptr[i])
      if (pipe(pip[i]) == -1)
	goto closepipes;

  if ((pid = fork()) == -1)
    goto closepipes;
  else if (pid == 0)
    {
      char		**params = (char**)bunny_alloca((nbr + 1) * sizeof(*params));
      va_list		lst;

      if (pip[0][1] != -1) // stdin pipe
	{
	  close(pip[0][1]);
	  dup2(pip[0][0], STDIN_FILENO);
	}
      if (pip[1][0] != -1) // stdout pipe
	{
	  close(pip[1][0]);
	  dup2(pip[1][1], STDOUT_FILENO);
	}
      if (pip[2][0] != -1) // stderr pipe
	{
	  close(pip[2][0]);
	  dup2(pip[2][1], STDERR_FILENO);
	}
      if (pip[3][1] != -1) // data input
	close(pip[3][1]);
      if (pip[4][0] != -1) // data output
	close(pip[4][0]);
      if (pip[5][1] != -1) // command input
	close(pip[5][1]);
      if (pip[6][0] != -1) // command output
	close(pip[6][0]);

      if (nbr != 0)
	{
	  va_start(lst, nbr);
	  for (i = 0; i < nbr; ++i)
	    params[i] = va_arg(lst, char*);
	  params[i] = NULL;
	  va_end(lst);
	  execve(params[0], params, env);
	  perror("execve in bunny_popen");
	  exit(EXIT_FAILURE);
	}
      bunny_freea(params);
      return (0);
    }

  if (pip[0][0] != -1) // stdin pipe
    close(pip[0][0]);
  subproc->_stdin = pip[0][1];

  if (pip[1][1] != -1) // stdout pipe
    close(pip[1][1]);
  subproc->_stdout = pip[1][0];

  if (pip[2][1] != -1) // stderr pipe
    close(pip[2][1]);
  subproc->_stderr = pip[2][0];

  if (pip[3][0] != -1) // data input
    close(pip[3][0]);
  subproc->custom_data_input = pip[3][1];

  if (pip[4][1] != -1) // data output
    close(pip[4][1]);
  subproc->custom_data_output = pip[4][0];

  if (pip[5][0] != -1) // command input
    close(pip[5][0]);
  subproc->custom_command_input = pip[5][1];

  if (pip[6][1] != -1) // command output
    close(pip[6][1]);
  subproc->custom_command_output = pip[6][0];

  subproc->pid = pid;
  scream_log_if(PATTERN, "unix", subproc, env, nbr, pid);
  return (pid);

 closepipes:
  for (i = 0; i < len; ++i)
    if (pip[i][0] != -1)
      {
	close(pip[i][0]);
	close(pip[i][1]);
      }
  scream_error_if(return (-1), errno, PATTERN, "unix", subproc, env, nbr, -1);
  return (-1);
#else
  return (-1);
#endif
}

