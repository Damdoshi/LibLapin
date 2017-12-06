/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file context.h
** Library of already programmed context that fulfill different purpose.
** Consider this part as modules to insert or tweak to insert in your program
** directly and not like a toolbox like other part of the bunny library.
*/

#ifndef				__LAPIN_CONTEXT_H__
# define			__LAPIN_CONTEXT_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** This structure is the corner stone of every context.
** All context defined in the bunny library will lay on it
** to work. They need you to set those fields before using
** them.
**
** The main_structure pointer is present to be set to your
** data address. It is mainly present to be passed to
** callbacks that may be additionnally provided by the context.
** It is also present in case you wish to create your own
** context with this "standard".
**
** The subcontext will allow you to do set callbacks that will
** be called by the foreground context. Note that those calls
** entirely depends of the context. About the return value,
** the behaviour should always to return the first not GO_ON
** value to bunny_loop.
**
** The screen pointer is the area where the pixel will be
** drawn. It may be the window, it may be something else.
**
** The next_context field is the id of the context that
** should be used after leaving the current one.
**
**
**
** A quite interesting exemple mixing the usage of a t_bunny_picture
** for screen and an additionnal display function in subcontext would
** be to resize the graphic output.
*/
typedef struct			s_bunny_context_runtime_info
{
  void				*main_structure;
  t_bunny_context		subcontext;
  t_bunny_buffer		*screen;
  size_t			next_context;
}				t_bunny_context_runtime_info;

/*!
**
*/
t_bunny_response		bunny_context_key(t_bunny_event_state	state,
						  t_bunny_keysym	sym,
						  void			*data);

/*!
**
*/
t_bunny_response		bunny_context_click(t_bunny_event_state	state,
						    t_bunny_mouse_button sym,
						    void		*data);

# include			"context/splash.h"
# include			"context/depth.h"
#endif	/*			__LAPIN_CONTEXT_H__			*/
