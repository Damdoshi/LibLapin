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

/*
** Context callback will call the event with the current context structure as data parameter
*/
t_bunny_key_function		bunny_context_key;
t_bunny_type_function		bunny_context_type;
t_bunny_click_function		bunny_context_click;
t_bunny_move_function		bunny_context_move;
t_bunny_wheel_function		bunny_context_wheel;
t_bunny_joy_connect_function	bunny_context_joy_connect;
t_bunny_joy_axis_function	bunny_context_joy_axis;
t_bunny_joy_button_function	bunny_context_joy_button;
t_bunny_get_focus_function	bunny_context_get_focus;
t_bunny_lost_focus_function	bunny_context_lost_focus;
t_bunny_resize_function		bunny_context_resize;
t_bunny_close_function		bunny_context_close;
t_bunny_loop_function		bunny_context_loop;
t_bunny_display_function	bunny_context_display;
t_bunny_message_response_function bunny_context_message;
t_bunny_connect_response_function bunny_context_connect;
t_bunny_entering_context_function bunny_context_entering;
t_bunny_leaving_context_function bunny_context_leaving;
t_bunny_async_computation_response_function bunny_context_async_computation;
t_bunny_event_response_function	bunny_context_event_response;

/*
** Context callback will call the event with the "main structre" pointer as data parameter
*/
t_bunny_key_function		bunny_subcontext_key;
t_bunny_type_function		bunny_subcontext_type;
t_bunny_click_function		bunny_subcontext_click;
t_bunny_move_function		bunny_subcontext_move;
t_bunny_wheel_function		bunny_subcontext_wheel;
t_bunny_joy_connect_function	bunny_subcontext_joy_connect;
t_bunny_joy_axis_function	bunny_subcontext_joy_axis;
t_bunny_joy_button_function	bunny_subcontext_joy_button;
t_bunny_get_focus_function	bunny_subcontext_get_focus;

t_bunny_lost_focus_function	bunny_subcontext_lost_focus;
t_bunny_resize_function		bunny_subcontext_resize;
t_bunny_close_function		bunny_subcontext_close;
t_bunny_loop_function		bunny_subcontext_loop;
t_bunny_display_function	bunny_subcontext_display;
t_bunny_message_response_function bunny_subcontext_message;
t_bunny_connect_response_function bunny_subcontext_connect;
t_bunny_entering_context_function bunny_subcontext_entering;
t_bunny_leaving_context_function bunny_subcontext_leaving;
t_bunny_async_computation_response_function bunny_subcontext_async_computation;
t_bunny_event_response_function	bunny_subcontext_event_response;

# define			bunny_declare_context(name)	\
  t_bunny_key_function		name ## _key;			\
  t_bunny_type_function		name ## _type;			\
  t_bunny_click_function	name ## _click;			\
  t_bunny_move_function		name ## _move;			\
  t_bunny_wheel_function	name ## _wheel;			\
  t_bunny_joy_connect_function	name ## _joy_connect;		\
  t_bunny_joy_axis_function	name ## _joy_axis;		\
  t_bunny_joy_button_function	name ## _joy_button;		\
  t_bunny_get_focus_function	name ## _get_focus;		\
  t_bunny_lost_focus_function	name ## _lost_focus;		\
  t_bunny_resize_function	name ## _resize;		\
  t_bunny_close_function	name ## _close;			\
  t_bunny_loop_function		name ## _loop;			\
  t_bunny_display_function	name ## _display;		\
  t_bunny_message_response_function name ## _message;		\
  t_bunny_connect_response_function name ## _connect;		\
  t_bunny_entering_context_function name ## _entering;		\
  t_bunny_leaving_context_function name ## _leaving;		\
  t_bunny_async_computation_response_function name ## _async_computation; \
  t_bunny_event_response_function name ## _event_response

# include			"context/box.h"
# include			"context/cinematic.h"
# include			"context/splash.h"
# include			"context/pentacle.h"
# include			"context/loading.h"
# include			"context/depth.h"
# include			"context/dressing.h"

#endif	/*			__LAPIN_CONTEXT_H__			*/
