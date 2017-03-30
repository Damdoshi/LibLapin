/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file unix.h
** Hash function. As bunny_security, they are not
** made to be safe in term of crack or hack.
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
** stdout its output
** etc.
**
*/
typedef struct		s_bunny_subprocess
{
  pid_t			pid;
  int			stdin;
  int			stdout;
  int			stderr;
  int			custom_data_input;
  int			custom_data_output;
  int			custom_command_input;
  int			custom_command_output;
}			t_bunny_subprocess;

/*!
**
**
**
*/
int			bunny_popen(t_bunny_subprocess		*subproc,
				    char			**env,
				    size_t			nbr,
				    ...);

/*!
**
**
*/
int			bunny_pclose(t_bunny_subprocess		*subproc,
				     int			delay_in_seconds);

#endif	/*		__LAPIN_UNIX_H__			*/

