// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_quad_line(const t_bunny_collision	*a,
					  const t_bunny_collision	*b)
{
  t_bunny_vertex_array *arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 4 * sizeof(arr->vertex[0]));
  const t_bunny_quad_collision *quad = &a->quad;
  const t_bunny_line_collision *line = &b->line;
  size_t	i;

  for (i = 0, arr->length = 4; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = quad->coord[i].x;
      arr->vertex[i].pos.y = quad->coord[i].y;
    }

  if (bunny_quad_collision_dot(arr, &line->coord[0]) ||
      bunny_quad_collision_dot(arr, &line->coord[1]))
    {
      bunny_freea(arr);
      return (true);
    }
  for (i = 0; i < 4; ++i)
    if (_bunny_collision_segment_intersection
	(quad->coord[i], quad->coord[(i + 1) % 4], line->coord[0], line->coord[1]))
      {
	bunny_freea(arr);
	return (true);
      }
  bunny_freea(arr);
  return (false);
}

