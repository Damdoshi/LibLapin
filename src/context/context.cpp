// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
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

t_bunny_response	bunny_context_click(t_bunny_event_state	state,
					    t_bunny_mouse_button sym,
					    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.button)
    return (x->subcontext.click(state, sym, data));
  return (GO_ON);
}

