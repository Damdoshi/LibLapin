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

/**
 * @doc
 * @doc-symbol bunny_popen
 * @doc-kind function
 * @doc-module unix
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Starts a subprocess and opens the requested communication pipes.
 * @description bunny_popen forks the current process, executes the requested program in the child process and creates the pipes requested in the t_bunny_subprocess structure.
 * @description Before calling bunny_popen, set each communication field of subprocess to true when you want the corresponding pipe to be opened, or false otherwise. On success, true values are replaced by parent-side file descriptors and unused fields are set to -1. The subprocess must later be closed with bunny_pclose.
 * @description The variadic parameters are command-line-like. The first one is the program path sent to execve, followed by its arguments. For example, a command like ls -l -a is represented with three variadic strings: "ls", "-l" and "-a".
 * @param subprocess The subprocess descriptor used both as input configuration and output descriptor storage.
 * @param environment The environment passed to the newly created process.
 * @param nbr_parameters The number of strings sent in the variadic part.
 * @param ... Variadic parameters. Each parameter must be a char pointer. The first one is the executed program, the following ones are its command-line arguments.
 * @return-case success Returns the pid of the created process.
 * @return-case failure Returns -1 if a pipe cannot be opened, if fork fails or if the function is unavailable on the current platform.
 * @error EMFILE The per-process limit on the number of open file descriptors has been reached.
 * @error ENFILE The system-wide limit on the total number of open files has been reached.
 * @error EAGAIN A system-imposed limit on the number of processes or threads was encountered.
 * @error ENOSYS fork is not supported on this platform.
 * @error ENOMEM Out of memory.
 * @log "unix"
 * @see t_bunny_subprocess
 * @see bunny_pclose
 *
 * @doc-lang fr
 * @brief Démarre un sous-processus et ouvre les tubes de communication demandés.
 * @description bunny_popen duplique le processus courant, exécute le programme demandé dans le processus fils et crée les tubes indiqués dans la structure t_bunny_subprocess.
 * @description Avant d'appeler bunny_popen, mettez chaque champ de communication de subprocess à true lorsque vous voulez ouvrir le tube correspondant, ou à false sinon. En cas de succès, les valeurs true sont remplacées par des descripteurs de fichiers côté parent et les champs inutilisés sont mis à -1. Le sous-processus doit ensuite être fermé avec bunny_pclose.
 * @description Les paramètres variadiques ressemblent à une ligne de commande. Le premier est le chemin du programme envoyé à execve, suivi de ses arguments. Par exemple, une commande comme ls -l -a est représentée avec trois chaînes variadiques : "ls", "-l" et "-a".
 * @param subprocess Le descripteur de sous-processus utilisé à la fois comme configuration d'entrée et comme stockage des descripteurs de sortie.
 * @param environment L'environnement transmis au processus nouvellement créé.
 * @param nbr_parameters Le nombre de chaînes envoyées dans la partie variadique.
 * @param ... Paramètres variadiques. Chaque paramètre doit être un pointeur sur char. Le premier est le programme exécuté, les suivants sont ses arguments de ligne de commande.
 * @return-case success Renvoie le pid du processus créé.
 * @return-case failure Renvoie -1 si un tube ne peut pas être ouvert, si fork échoue ou si la fonction n'est pas disponible sur la plateforme courante.
 * @error EMFILE La limite de descripteurs de fichiers ouverts par processus a été atteinte.
 * @error ENFILE La limite globale du système concernant le nombre total de fichiers ouverts a été atteinte.
 * @error EAGAIN Une limite imposée par le système sur le nombre de processus ou de threads a été rencontrée.
 * @error ENOSYS fork n'est pas supporté sur cette plateforme.
 * @error ENOMEM Mémoire insuffisante.
 * @log "unix"
 * @see t_bunny_subprocess
 * @see bunny_pclose
 */

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

