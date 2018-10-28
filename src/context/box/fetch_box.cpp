// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_gui_box		*bunny_fetch_box(t_bunny_gui_box	*box,
					 const t_bunny_position	*pos)
{
  t_bunny_map		**node;

  for (bunny_map_all(box->children, node))
    {
      t_bunny_gui_box	*x = bunny_map_data(*node, t_bunny_gui_box*);

      if (pos->x >= x->position.x &&
	  pos->y >= x->position.y &&
	  pos->x < x->position.x + x->size.x &&
	  pos->y < x->position.y + x->size.y)
	return (x);
    }
  return (NULL);
}
