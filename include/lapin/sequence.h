/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

/*!
** \file sequence.h
**
** What is the difference between a sequence and a function?
** A sequence is iterative, each call to execute only do a single
** step. Expression and function called are considered as a step!
** But other sequence called are stepped too.
**
** Recursivity does not work currently.
*/

#ifndef			__LAPIN_SEQUENCE_H__
# define		__LAPIN_SEQUENCE_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

typedef enum		e_bunny_sequence_decision
  {
    BSD_ERROR		= -1,
    BSD_STAY,
    BSD_STEP,
    BSD_PLAY_NEXT
  }			t_bunny_sequence_decision;

typedef t_bunny_sequence_decision (*t_bunny_sequence_fallback_function)
(t_bunny_configuration	*seq,
 const char		*cmd,
 t_bunny_configuration	**params,
 void			*data);

typedef t_bunny_sequence_decision (*t_bunny_sequence_fallback_event)
(t_bunny_configuration	*seq,
 t_bunny_event		*evt,
 const char		*cmd,
 t_bunny_configuration	**params,
 void			*data);

//

typedef t_bunny_sequence_decision (*t_bunny_sequence_command_function)
(t_bunny_configuration	*seq,
 t_bunny_configuration	**params,
 void			*data);

typedef t_bunny_sequence_decision (*t_bunny_sequence_command_event)
(t_bunny_configuration	*seq,
 t_bunny_event		*evt,
 t_bunny_configuration	**params,
 void			*data);

typedef t_bunny_sequence_decision t_bunny_sequence_commandf
(t_bunny_configuration	*seq,
 t_bunny_configuration	**params,
 void			*data);

t_bunny_sequence_commandf
  bunny_sequence_if,
  bunny_sequence_else_if,
  bunny_sequence_else,
  bunny_sequence_endif,
  bunny_sequence_goto,
  bunny_sequence_exec,
  bunny_sequence_wait,
  bunny_sequence_wait_loop,
  bunny_sequence_print,
  bunny_sequence_printerr,
  bunny_sequence_return
  ;

typedef struct		s_bunny_sequence_command
{
  t_bunny_sequence_command_function init;
  t_bunny_sequence_command_function loop;
  t_bunny_sequence_command_event event;
}			t_bunny_sequence_command;

typedef struct		s_bunny_sequence_fallback_command
{
  t_bunny_sequence_fallback_function init;
  t_bunny_sequence_fallback_function loop;
  t_bunny_sequence_fallback_event event;
}			t_bunny_sequence_fallback_command;

/*
**
*/
t_bunny_response	bunny_sequence_execute(t_bunny_configuration		*cnf,
					       t_bunny_configuration		*params,
					       t_bunny_sequence_fallback_function ucmd,
					       t_bunny_sequence_fallback_function urpt,
					       t_bunny_sequence_fallback_event	uevt,
					       void				*dat);
const char		*bunny_sequence_debug(t_bunny_configuration		*cnf);
bool			bunny_sequence_terminated(t_bunny_configuration		*cnf);

#endif	/*		__LAPIN_SEQUENCE_H__					*/
