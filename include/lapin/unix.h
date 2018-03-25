/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file unix.h
** Bring system utilities. Currently an heavy version
** of popen and pclose.
*/

#ifndef			__LAPIN_UNIX_H__
# define		__LAPIN_UNIX_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# include		<stdarg.h>
# include		<unistd.h>

/*!
** The pid and all I/Os of the subprocess.
** stdin is the stdin *of the subprocess*: where it reads everything.
** stdout is its main output.
** stderr is its error output.
** custom_data_input and custom_data_output are custom I/O that may
** be opened freely, these I/O are for datas.
** custom_command_input and custom_command_output are custom I/O that
** may be opened freely, these I/O are for commands.
*/
typedef struct		s_bunny_subprocess
{
  pid_t			pid;
  int			_stdin;
  int			_stdout;
  int			_stderr;
  int			custom_data_input;
  int			custom_data_output;
  int			custom_command_input;
  int			custom_command_output;
}			t_bunny_subprocess;

/*!
** Start a program with different inputs, outputs and parameters.
** \param subproc A I/O structure that should contains true or false value for
** each input or output. A true value indicates a pipe is required, a false
** does nothing. This parameter is also an output and contains associated file
** descriptor and pid.
** \param env The environment of the started program
** \param nbr The amount of parameters
** \param ... Variadics parameters. Only char*, the first one is the program itself.
** \return Return the pid of the started program or -1 on error.
*/
int			bunny_popen(t_bunny_subprocess		*subproc,
				    char			**env,
				    size_t			nbr,
				    ...);

/*!
** Stop the program opened throught a bunny_popen that have its pid registered
** in the sent subproc structure. Close all pipes.
** The delay_in_seconds is a maximum delay before killing the child program
** with SIGINT.
** \param subproc A subprocess structure started with bunny_popen
** \param delay_in_seconds A delay before killing the subprocess with SIGINT
** \return Return the end status of the subprocess, or 0 if the program was killed.
*/
int			bunny_pclose(t_bunny_subprocess		*subproc,
				     int			delay_in_seconds);

#endif	/*		__LAPIN_UNIX_H__			*/

