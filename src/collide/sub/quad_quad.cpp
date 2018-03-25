// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_quad_quad(const t_bunny_collision	*a,
					  const t_bunny_collision	*b)
{
  t_bunny_vertex_array *arra = (t_bunny_vertex_array*)bunny_alloca(sizeof(arra->length) + 4 * sizeof(arra->vertex[0]));
  t_bunny_vertex_array *arrb = (t_bunny_vertex_array*)bunny_alloca(sizeof(arrb->length) + 4 * sizeof(arrb->vertex[0]));
  const t_bunny_quad_collision *aquad = &a->quad;
  const t_bunny_quad_collision *bquad = &b->quad;
  t_bunny_line_collision qline;
  t_bunny_line_collision tline;
  t_bunny_accurate_position tmp;
  size_t	i;

  for (i = 0, arra->length = 4; i < arra->length; ++i)
    {
      arra->vertex[i].pos.x = aquad->coord[i].x;
      arra->vertex[i].pos.y = aquad->coord[i].y;
      arrb->vertex[i].pos.x = bquad->coord[i].x;
      arrb->vertex[i].pos.y = bquad->coord[i].y;
    }

  /// CHECK IF INSIDE
  for (i = 0; i < 4; ++i)
    {
      tmp = aquad->coord[i];
      if (bunny_quad_collision_dot(arra, &tmp))
	goto collide;
      tmp = bquad->coord[i];
      if (bunny_quad_collision_dot(arrb, &tmp))
	goto collide;
    }

  /// CHECK IF CROSSED
  qline.intermediate_points = 0;
  tline.intermediate_points = 0;

  qline.coord[0] = tline.coord[0];
  qline.coord[1] = tline.coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;
  qline.coord[0] = tline.coord[1];
  qline.coord[1] = tline.coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;
  qline.coord[0] = tline.coord[2];
  qline.coord[1] = tline.coord[3];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;
  qline.coord[0] = tline.coord[3];
  qline.coord[1] = tline.coord[0];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  bunny_freea(arra);
  bunny_freea(arrb);
  return (false);

 collide:
  bunny_freea(arra);
  bunny_freea(arrb);
  return (true);
}
