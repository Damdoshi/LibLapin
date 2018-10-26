// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static void		display_simple_box(t_bunny_box_system		*sys,
					   t_bunny_gui_box		*box,
					   const t_bunny_accurate_position *off)
{
  if (box->color.full == 0)
    return;
  t_bunny_accurate_position n = {off->x + box->position.x, off->y + box->position.y};
  t_bunny_vertex_array	*vx;

  vx = (t_bunny_vertex_array*)bunny_alloca(sizeof(vx->length) + 4 * sizeof(vx->vertex[0]));
  vx->length = 4;

  vx->vertex[0].pos.x = n.x;
  vx->vertex[0].pos.y = n.y;
  vx->vertex[0].color = box->color.full;

  vx->vertex[1].pos.x = n.x + box->size.x;
  vx->vertex[1].pos.y = n.y;
  vx->vertex[1].color = box->color.full;

  vx->vertex[2].pos.x = n.x + box->size.x;
  vx->vertex[2].pos.y = n.y + box->size.y;
  vx->vertex[2].color = box->color.full;

  vx->vertex[3].pos.x = n.x;
  vx->vertex[3].pos.y = n.y + box->size.y;
  vx->vertex[3].color = box->color.full;

  bunny_set_geometry(sys->head.screen, BGY_QUADS, vx, NULL);
  bunny_freea(vx);
}

t_bunny_gui_box		*bunny_new_simple_box(t_bunny_gui_box		*parent,
					      t_bunny_configuration	*cnf)
{
  t_bunny_gui_box	*nw;

  if ((nw = (t_bunny_gui_box*)bunny_new_gui_box(sizeof(*nw), cnf)) == NULL)
    return (NULL);
  nw->type = BBT_SIMPLE_BOX;
  nw->destructor = NULL;
  nw->display = display_simple_box;
  nw->parent = parent;
  nw->configuration = cnf;
  if (bunny_accurate_position_configuration("Position", &nw->position, cnf) == false)
    goto Error;
  if (bunny_accurate_position_configuration("Size", &nw->size, cnf) == false)
    goto Error;
  bunny_color_configuration("Color", &nw->color, cnf);
  return (nw);

 Error:
  bunny_delete_box(nw);
  return (NULL);
}

