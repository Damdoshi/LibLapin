// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_triangle_line(const t_bunny_collision	*a,
						      const t_bunny_collision	*b)
{
  t_bunny_vertex_array	*arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 3 * sizeof(arr->vertex[0]));
  const t_bunny_triangle_collision *triangle = &a->triangle;
  const t_bunny_line_collision *line = &b->line;
  size_t		i;

  for (i = 0, arr->length = 3; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = triangle->coord[i].x;
      arr->vertex[i].pos.y = triangle->coord[i].y;
    }

  if (bunny_triangle_collision_dot(arr, &line->coord[0]) ||
      bunny_triangle_collision_dot(arr, &line->coord[1]) ||
      _bunny_collision_segment_intersection(triangle->coord[0], triangle->coord[1], line->coord[0], line->coord[1]) ||
      _bunny_collision_segment_intersection(triangle->coord[1], triangle->coord[2], line->coord[0], line->coord[1]) ||
      _bunny_collision_segment_intersection(triangle->coord[2], triangle->coord[0], line->coord[0], line->coord[1]))
    {
      bunny_freea(arr);
      return (true);
    }
  bunny_freea(arr);
  return (false);
}

