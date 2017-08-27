// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

//
// Weakness: If the triangle is fully on the disc of the circle,
// then, it is not detected. One of the hot spot of the circle
// must be inside the triangle.
//

bool			bunny_collision_triangle_circle(const t_bunny_collision	*a,
							const t_bunny_collision	*b)
{
  t_bunny_vertex_array	*arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 3 * sizeof(arr->vertex[0]));
  const t_bunny_triangle_collision *triangle = &a->triangle;
  const t_bunny_circle_collision *circle = &b->circle;
  t_bunny_accurate_position tmp;
  size_t		i;

  for (i = 0, arr->length = 3; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = triangle->coord[i].x;
      arr->vertex[i].pos.y = triangle->coord[i].y;
    }
  for (i = 0; _get_point_on_circle(&circle->coord, circle->radius, i, &tmp); ++i)
    if (bunny_triangle_collision_dot(arr, &tmp))
      {
	bunny_freea(arr);
	return (true);
      }
  bunny_freea(arr);
  return (false);
}

