// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_set_wheel_response(t_bunny_wheel	w)
{
  gl_callback.wheel = w;
}

void			bunny_set_text_response(t_bunny_type	type)
{
  gl_callback.type = type;
}

void			bunny_set_move_response(t_bunny_move	move)
{
  gl_callback.move = move;
}

void			bunny_set_lost_focus_response(t_bunny_lost_focus	j)
{
  gl_callback.lost_focus = j;
}

void			bunny_set_joy_connect_response(t_bunny_joy_connect	j)
{
  gl_callback.connect = j;
}

void			bunny_set_joy_axis_response(t_bunny_joy_axis	j)
{
  gl_callback.axis = j;
}

void			bunny_set_connect_response(t_bunny_connect_response func)
{
  gl_callback.netconnect = func;
}

void			bunny_set_click_response(t_bunny_click	click)
{
  gl_callback.click = click;
}

void			bunny_set_close_response(t_bunny_close	j)
{
  gl_callback.close = j;
}

void			bunny_set_get_focus_response(t_bunny_get_focus	j)
{
  gl_callback.get_focus = j;
}

void			bunny_set_joy_button_response(t_bunny_joy_button	j)
{
  gl_callback.button = j;
}

void			bunny_set_key_response(t_bunny_key	key)
{
  gl_callback.key = key;
}

void			bunny_set_message_response(t_bunny_message_response func)
{
  gl_callback.netmessage = func;
}

void			bunny_set_resize_response(t_bunny_resize	j)
{
  gl_callback.resize = j;
}

void			bunny_set_leaving_context_response(t_bunny_leaving_context func)
{
  gl_callback.leaving_context = func;
}

void			bunny_set_entering_context_response(t_bunny_loop func)
{
  gl_callback.entering_context = func;
}
