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

/**
 * @doc
 * @doc-symbol bunny_pclose
 * @doc-kind function
 * @doc-module unix
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Closes a subprocess opened with bunny_popen.
 * @description bunny_pclose closes all communication descriptors stored in subprocess, waits up to delay_in_seconds for the child process to terminate, then sends SIGINT to it if the delay expires.
 * @description The function may return before the delay expires when the subprocess terminates by itself. On unsupported platforms, the function returns -1.
 * @param subprocess A subprocess structure previously filled by bunny_popen.
 * @param delay_in_seconds The maximum delay, in seconds, before sending SIGINT to the subprocess. If this value is zero, SIGINT is sent immediately.
 * @return-case terminated Returns the status reported by waitpid when the subprocess terminates before the delay expires.
 * @return-case killed Returns 0 if the subprocess is killed after the delay expires.
 * @return-case unsupported Returns -1 when the function is not available on the current platform.
 * @log "unix"
 * @see t_bunny_subprocess
 * @see bunny_popen
 *
 * @doc-lang fr
 * @brief Ferme un sous-processus ouvert avec bunny_popen.
 * @description bunny_pclose ferme tous les descripteurs de communication stockés dans subprocess, attend jusqu'à delay_in_seconds que le processus fils se termine, puis lui envoie SIGINT si le délai expire.
 * @description La fonction peut revenir avant l'expiration du délai lorsque le sous-processus se termine de lui-même. Sur les plateformes non supportées, la fonction renvoie -1.
 * @param subprocess Une structure de sous-processus précédemment remplie par bunny_popen.
 * @param delay_in_seconds Le délai maximal, en secondes, avant d'envoyer SIGINT au sous-processus. Si cette valeur vaut zéro, SIGINT est envoyé immédiatement.
 * @return-case terminated Renvoie le statut indiqué par waitpid lorsque le sous-processus se termine avant l'expiration du délai.
 * @return-case killed Renvoie 0 si le sous-processus est tué après l'expiration du délai.
 * @return-case unsupported Renvoie -1 lorsque la fonction n'est pas disponible sur la plateforme courante.
 * @log "unix"
 * @see t_bunny_subprocess
 * @see bunny_popen
 */

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

