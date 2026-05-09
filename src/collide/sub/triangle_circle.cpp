// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_triangle_circle(const t_bunny_collision	*a,
							const t_bunny_collision	*b)
{
  t_bunny_vertex_array	*arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 3 * sizeof(arr->vertex[0]));
  const t_bunny_triangle_collision *triangle = &a->triangle;
  const t_bunny_circle_collision *circle = &b->circle;
  double		rad = circle->radius;
  size_t		i;

  if (rad < 0)
    rad = -rad;
  for (i = 0, arr->length = 3; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = triangle->coord[i].x;
      arr->vertex[i].pos.y = triangle->coord[i].y;
    }

  if (bunny_triangle_collision_dot(arr, &circle->coord))
    goto collide;
  for (i = 0; i < 3; ++i)
    if (_bunny_collision_distance_square(triangle->coord[i], circle->coord) <= rad * rad)
      goto collide;
  for (i = 0; i < 3; ++i)
    if (_bunny_collision_point_segment_distance_square
	(triangle->coord[i], triangle->coord[(i + 1) % 3], circle->coord) <= rad * rad)
      goto collide;

  bunny_freea(arr);
  return (false);

 collide:
  bunny_freea(arr);
  return (true);
}

