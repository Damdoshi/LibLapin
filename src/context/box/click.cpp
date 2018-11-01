// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_box_click(t_bunny_event_state	state,
					t_bunny_mouse_button	button,
					void			*data);

static t_bunny_response	search_box(t_bunny_event_state		state,
				   t_bunny_mouse_button		button,
				   void				*data,
				   t_bunny_gui_box		*box,
				   t_bunny_position		pos)
{
  t_bunny_box_system	*sys = (t_bunny_box_system*)data;
  t_bunny_gui_box	*fnd;
  t_bunny_response	ret;

  if (box->inactive)
    return (NOTHING_HAPPENED);

  if (pos.x < box->position.x ||
      pos.y < box->position.y ||
      pos.x > box->position.x + box->size.x ||
      pos.y > box->position.y + box->size.y)
    return (NOTHING_HAPPENED);
  pos.x -= box->position.x;
  pos.y -= box->position.y;

  if ((fnd = bunny_fetch_box(box, &pos)) == NULL)
    {
      if (state == GO_DOWN)
	{
	  if (sys->focus && sys->focus->focus)
	    if ((ret = sys->focus->focus(LOST_FOCUS, sys, sys->focus)) < GO_ON)
	      return (GO_ON);

	  if (!box->focus)
	    sys->focus = NULL;
	  else
	    {
	      sys->focus = box;
	      if (box->focus)
		if ((ret = box->focus(GOT_FOCUS, sys, box)) < GO_ON)
		  return (GO_ON);
	    }

	}
      if (box->mouse_button)
	return (box->mouse_button(state, pos, button, sys, box));
      return (NOTHING_HAPPENED);
    }
  return (search_box(state, button, data, fnd, pos));
}

t_bunny_response	bunny_box_click(t_bunny_event_state	state,
					t_bunny_mouse_button	button,
					void			*data)
{
  const t_bunny_position *mpos = bunny_get_mouse_position();
  t_bunny_box_system	*box = (t_bunny_box_system*)data;
  t_bunny_gui_box	*x = &box->screen;
  t_bunny_response	ret;

  if ((ret = search_box(state, button, data, x, *mpos)) < GO_ON)
    return (ret);
  if (ret == NOTHING_HAPPENED)
    {
      box->focus = NULL;
      if (box->head.subcontext.button)
	if ((ret = box->head.subcontext.click(state, button, data)) < GO_ON)
	  return (ret);
      if (box->subhead)
	if ((ret = box->subhead->subcontext.click(state, button, data)) < GO_ON)
	  return (ret);
    }
  return (ret);
}

