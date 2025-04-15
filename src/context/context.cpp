// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_context_key(t_bunny_event_state	state,
					  t_bunny_keysym	sym,
					  void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.key)
    return (x->subcontext.key(state, sym, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_type(uint32_t		unicode,
					   void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.type)
    return (x->subcontext.type(unicode, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_click(t_bunny_event_state	state,
					    t_bunny_mouse_button sym,
					    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.button)
    return (x->subcontext.click(state, sym, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_move(const t_bunny_position *rel,
					   void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.move)
    return (x->subcontext.move(rel, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_wheel(int			wheelid,
					    int			delta,
					    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.wheel)
    return (x->subcontext.wheel(wheelid, delta, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_joy_connect(t_bunny_event_state	state,
						  int		joyid,
						  const t_bunny_joystick *joyinfo,
						  void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.connect)
    return (x->subcontext.connect(state, joyid, joyinfo, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_joy_axis(int		joyid,
					       t_bunny_axis	axis,
					       float		value,
					       void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.axis)
    return (x->subcontext.axis(joyid, axis, value, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_joy_button(t_bunny_event_state state,
						 int		joyid,
						 int		button,
						 void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.button)
    return (x->subcontext.button(state, joyid, button, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_get_focus(const t_bunny_window *win,
						void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.get_focus)
    return (x->subcontext.get_focus(win, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_lost_focus(const t_bunny_window *win,
						 void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.lost_focus)
    return (x->subcontext.lost_focus(win, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_resize(const t_bunny_window *win,
					     const t_bunny_position *siz,
					     void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.resize)
    return (x->subcontext.resize(win, siz, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_close(const t_bunny_window *win,
					    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.close)
    return (x->subcontext.close(win, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_loop(void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.loop)
    return (x->subcontext.loop(data));
  return (GO_ON);
}

t_bunny_response	bunny_context_display(void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.display)
    return (x->subcontext.display(data));
  return (GO_ON);
}

t_bunny_response	bunny_context_message(int		fd,
					      const void	*buffer,
					      size_t		siz,
					      void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.netmessage && x->subcontext.netcom)
    return (x->subcontext.netmessage(fd, buffer, siz, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_connect(int		fd,
					      t_bunny_event_state state,
					      void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.netconnect && x->subcontext.netcom)
    return (x->subcontext.netconnect(fd, state, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_entering(void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.entering_context)
    return (x->subcontext.entering_context(data));
  return (GO_ON);
}

void			bunny_context_leaving(t_bunny_response	res,
					      void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.leaving_context)
    x->subcontext.leaving_context(res, data);
}

t_bunny_response	bunny_context_async_computation(void	*cmt,
							void	*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.async_computation_response)
    return (x->subcontext.async_computation_response(cmt, data));
  return (GO_ON);
}

t_bunny_response	bunny_context_event_response(const t_bunny_event *event,
						     void *data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.event)
    return (x->subcontext.event(event, data));
  return (GO_ON);
}

