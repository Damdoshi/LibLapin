// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_display_simple_box(t_bunny_box_system		*sys,
						 t_bunny_gui_box		*box,
						 const t_bunny_accurate_position *off)
{
  //if (box->color.full == 0) // Changer par "hidden"/invisible, etc.
    //return (GO_ON);
  t_bunny_accurate_position n = {off->x + box->position.x, off->y + box->position.y};
  t_bunny_vertex_array	*vx;
  t_bunny_picture	*pic;
  t_bunny_color		col;

  vx = (t_bunny_vertex_array*)bunny_alloca(sizeof(vx->length) + 4 * sizeof(vx->vertex[0]));
  vx->length = 4;

  pic = box->background;
  col.full = box->color.full;
  if (sys->down_clicked == box && box->clicked_color.full != 0)
    {
      pic = box->clicked_background;
      col.full = box->clicked_color.full;
    }
  else if (sys->hovered == box && box->hovered_color.full != 0)
    {
      pic = box->hovered_background;
      col.full = box->hovered_color.full;
    }
  else if (sys->focus == box && box->focused_color.full != 0)
    {
      pic = box->focused_background;
      col.full = box->focused_color.full;
    }

  vx->vertex[0].pos.x = n.x;
  vx->vertex[0].pos.y = n.y;
  vx->vertex[0].color = col.full;

  vx->vertex[1].pos.x = n.x + box->size.x;
  vx->vertex[1].pos.y = n.y;
  vx->vertex[1].color = col.full;

  vx->vertex[2].pos.x = n.x + box->size.x;
  vx->vertex[2].pos.y = n.y + box->size.y;
  vx->vertex[2].color = col.full;

  vx->vertex[3].pos.x = n.x;
  vx->vertex[3].pos.y = n.y + box->size.y;
  vx->vertex[3].color = col.full;

  if (pic)
    if (box->background_mode == BPDM_STRETCH)
      {
	vx->vertex[0].tex.x = pic->clip_x_position;
	vx->vertex[0].tex.y = pic->clip_y_position;
	vx->vertex[1].tex.x = pic->clip_x_position + pic->clip_width;
	vx->vertex[1].tex.y = pic->clip_y_position;
	vx->vertex[2].tex.x = pic->clip_x_position + pic->clip_width;
	vx->vertex[2].tex.y = pic->clip_y_position + pic->clip_height;
	vx->vertex[3].tex.x = pic->clip_x_position;
	vx->vertex[3].tex.y = pic->clip_y_position + pic->clip_height;
      }
  // else if other display mode
  bunny_set_geometry(sys->head.screen, BGY_QUADS, vx, pic);
  bunny_freea(vx);

  return (GO_ON);
}
