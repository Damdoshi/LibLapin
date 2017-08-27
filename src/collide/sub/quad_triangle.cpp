// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	<alloca.h>
#include	"lapin_private.h"

bool		bunny_collision_quad_triangle(const t_bunny_collision	*a,
					      const t_bunny_collision	*b)
{
  t_bunny_vertex_array *arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 4 * sizeof(arr->vertex[0]));
  const t_bunny_quad_collision *quad = &a->quad;
  const t_bunny_triangle_collision *triangle = &b->triangle;
  t_bunny_line_collision qline;
  t_bunny_line_collision tline;
  t_bunny_accurate_position tmp;
  size_t	i;

  for (i = 0, arr->length = 4; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = quad->coord[i].x;
      arr->vertex[i].pos.y = quad->coord[i].y;
    }

  /// CHECK IF INSIDE
  for (i = 0; i < 3; ++i)
    {
      tmp = triangle->coord[i];
      if (bunny_quad_collision_dot(arr, &tmp))
	goto collide;
    }

  /// CHECK IF CROSSED
  qline.intermediate_points = 0;
  tline.intermediate_points = 0;

  qline.coord[0].x = quad->coord[0].x;
  qline.coord[0].y = quad->coord[0].y;
  qline.coord[1].x = quad->coord[0].x;
  qline.coord[1].y = quad->coord[0].y + quad->coord[1].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  qline.coord[0].x = quad->coord[0].x;
  qline.coord[0].y = quad->coord[0].y;
  qline.coord[1].x = quad->coord[0].x + quad->coord[1].x;
  qline.coord[1].y = quad->coord[0].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  qline.coord[0].x = quad->coord[0].x + quad->coord[1].x;
  qline.coord[0].y = quad->coord[0].y;
  qline.coord[1].x = quad->coord[0].x + quad->coord[1].x;
  qline.coord[1].y = quad->coord[0].y + quad->coord[1].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;
  
  qline.coord[0].x = quad->coord[0].x;
  qline.coord[0].y = quad->coord[0].y + quad->coord[1].x;
  qline.coord[1].x = quad->coord[0].x + quad->coord[1].x;
  qline.coord[1].y = quad->coord[0].y + quad->coord[1].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&qline, (t_bunny_collision*)&tline))
    goto collide;

  bunny_freea(arr);
  return (false);

 collide:
  bunny_freea(arr);
  return (true);
}

