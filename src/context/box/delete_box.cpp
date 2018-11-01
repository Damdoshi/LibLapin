// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static void		_bunny_delete_box_rec(t_bunny_map		*map,
					      void			*d)
{
  t_bunny_gui_box	*box = bunny_map_data(map, t_bunny_gui_box*);

  (void)d;
  if (box)
    bunny_delete_box(box);
}

void			bunny_delete_box(t_bunny_gui_box	*box)
{
  if (box->id)
    bunny_free((char*)box->id);
  if (box->children)
    {
      bunny_map_foreach(box->children, _bunny_delete_box_rec, NULL);
      bunny_delete_map(box->children);
    }

  if (box->focused_background)
    bunny_delete_clipable(box->focused_background);
  if (box->clicked_background)
    bunny_delete_clipable(box->clicked_background);
  if (box->hovered_background)
    bunny_delete_clipable(box->hovered_background);
  if (box->background)
    bunny_delete_clipable(box->background);

  if (box->destructor)
    box->destructor(box);
  bunny_free(box);
}

