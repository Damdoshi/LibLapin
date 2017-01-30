// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static double		 _scalar(const t_bunny_accurate_position			*a,
				 const t_bunny_accurate_position			*b)
{
  return (a->x * b->x + a->y * b->y);
}

bool			bunny_triangle_collision_dot(const t_bunny_vertex_array		*v3,
						     const t_bunny_accurate_position	*dot)
{
  t_bunny_accurate_position vec[3];
  double		scalar[5];
  double		inv;
  double		u, v;

  if (v3->length != 3)
    return (false);
  vec[0].x = v3->vertex[2].pos.x - v3->vertex[0].pos.x;
  vec[0].y = v3->vertex[2].pos.y - v3->vertex[0].pos.y;

  vec[1].x = v3->vertex[1].pos.x - v3->vertex[0].pos.x;
  vec[1].y = v3->vertex[1].pos.y - v3->vertex[0].pos.y;

  vec[2].x = dot->x - v3->vertex[0].pos.x;
  vec[2].y = dot->y - v3->vertex[0].pos.y;

  scalar[0] = _scalar(&vec[0], &vec[0]);
  scalar[1] = _scalar(&vec[0], &vec[1]);
  scalar[2] = _scalar(&vec[0], &vec[2]);
  scalar[3] = _scalar(&vec[1], &vec[1]);
  scalar[4] = _scalar(&vec[1], &vec[2]);

  inv = 1.0 / (scalar[0] * scalar[3] - scalar[1] * scalar[1]);
  u = (scalar[3] * scalar[2] - scalar[1] * scalar[4]) * inv;
  v = (scalar[0] * scalar[4] - scalar[1] * scalar[2]) * inv;

  return ((u >= 0) && (v >= 0) && (u + v < 1));
}

