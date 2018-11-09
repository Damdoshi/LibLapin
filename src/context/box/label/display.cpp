// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_display_simple_box(t_bunny_box_system		*sys,
						 t_bunny_gui_box		*box,
						 const t_bunny_accurate_position *off);

t_bunny_response	bunny_display_label_box(t_bunny_box_system		*sys,
						t_bunny_gui_box			*box,
						const t_bunny_accurate_position	*off)
{
  t_bunny_accurate_position n = {off->x + box->position.x, off->y + box->position.y};
  t_bunny_gui_label	*lab = (t_bunny_gui_label*)box;
  t_bunny_picture	*pic = &lab->text->clipable;
  t_bunny_vertex_array	*vx;
  t_bunny_response	ret;

  if ((ret = bunny_display_simple_box(sys, box, off)) < GO_ON)
    return (ret);

  bunny_clear(&lab->text->clipable.buffer, 0);
  lab->text->string_len = strlen(lab->text->string);
  bunny_draw(&lab->text->clipable);

  vx = (t_bunny_vertex_array*)bunny_alloca(sizeof(vx->length) + 4 * sizeof(vx->vertex[0]));
  vx->length = 4;

  vx->vertex[0].pos.x = n.x;
  vx->vertex[0].pos.y = n.y;
  vx->vertex[0].color = 0;
  vx->vertex[0].tex.x = pic->clip_x_position;
  vx->vertex[0].tex.y = pic->clip_y_position;

  vx->vertex[1].pos.x = n.x + box->size.x;
  vx->vertex[1].pos.y = n.y;
  vx->vertex[1].color = 0;
  vx->vertex[1].tex.x = pic->clip_x_position + pic->clip_width;
  vx->vertex[1].tex.y = pic->clip_y_position;

  vx->vertex[2].pos.x = n.x + box->size.x;
  vx->vertex[2].pos.y = n.y + box->size.y;
  vx->vertex[2].color = 0;
  vx->vertex[2].tex.x = pic->clip_x_position + pic->clip_width;
  vx->vertex[2].tex.y = pic->clip_y_position + pic->clip_height;

  vx->vertex[3].pos.x = n.x;
  vx->vertex[3].pos.y = n.y + box->size.y;
  vx->vertex[3].color = 0;
  vx->vertex[3].tex.x = pic->clip_x_position;
  vx->vertex[3].tex.y = pic->clip_y_position + pic->clip_height;

  bunny_set_geometry(sys->head.screen, BGY_QUADS, vx, pic);
  bunny_freea(vx);
  return (GO_ON);
}

