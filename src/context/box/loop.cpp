// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

typedef std::pair<t_bunny_box_system*, double> _bunny_packet;

static t_bunny_response loop_box(t_bunny_box_system	*sys,
				 t_bunny_gui_box	*box,
				 double			delay);

static void		broadcast_box(t_bunny_map	*nod,
				      void		*x)
{
  _bunny_packet		*sys = (_bunny_packet*)x;
  t_bunny_gui_box	*box = bunny_map_data(nod, t_bunny_gui_box*);
  t_bunny_response	ret;

  if ((ret = loop_box(sys->first, box, sys->second)) < GO_ON)
    throw ret;
}

static t_bunny_response loop_box(t_bunny_box_system	*sys,
				 t_bunny_gui_box	*box,
				 double			delay)
{
  t_bunny_response	ret;

  if (box->inactive)
    return (GO_ON);

  if (box->loop)
    if ((ret = box->loop(sys, box, delay)) != GO_ON)
      return (ret);
  if (box->children)
    {
      _bunny_packet	p;

      p.first = sys;
      p.second = delay;
      bunny_map_foreach(box->children, broadcast_box, &p);
    }
  return (GO_ON);
}

t_bunny_response	bunny_box_loop(void		*d)
{
  t_bunny_box_system	*sys = (t_bunny_box_system*)d;
  t_bunny_response	ret;

  if ((ret = loop_box(sys, &sys->screen, 1.0 / bunny_get_frequency())) < GO_ON)
    return (ret);
  return (GO_ON);
}

