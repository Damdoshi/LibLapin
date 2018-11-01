// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

typedef std::pair<t_bunny_box_system*, t_bunny_accurate_position> _bunny_packet;

static t_bunny_response	display_box(t_bunny_box_system			*sys,
				    t_bunny_gui_box			*box,
				    const t_bunny_accurate_position	*off);

static void		broadcast_box(t_bunny_map			*nod,
				      void				*x)
{
  _bunny_packet		*sys = (_bunny_packet*)x;
  t_bunny_gui_box	*box = bunny_map_data(nod, t_bunny_gui_box*);
  t_bunny_response	ret;

  if ((ret = display_box(sys->first, box, &sys->second)) < GO_ON)
    throw ret;
}

static t_bunny_response display_box(t_bunny_box_system			*sys,
				    t_bunny_gui_box			*box,
				    const t_bunny_accurate_position	*off)
{
  t_bunny_response	ret;

  if (box->hidden)
    return (GO_ON);

  if (box->display)
    if ((ret = box->display(sys, box, off)) != GO_ON)
      return (ret);
  if (box->children)
    {
      _bunny_packet	p;

      p.first = sys;
      p.second.x = off->x + box->position.x;
      p.second.y = off->y + box->position.y;
      bunny_map_foreach(box->children, broadcast_box, &p);
    }
  return (GO_ON);
}

t_bunny_response	bunny_box_display(void				*_sys)
{
  t_bunny_box_system	*sys = (t_bunny_box_system*)_sys;
  t_bunny_accurate_position x = {0, 0};
  t_bunny_response	ret;

  try
    {
      if ((ret = display_box(sys, &sys->screen, &x)) != GO_ON)
	return (ret);
    }
  catch (t_bunny_response r)
    {
      return (r);
    }
  if (sys->head.subcontext.display)
    return (sys->head.subcontext.display(sys));
  return (GO_ON);
}

