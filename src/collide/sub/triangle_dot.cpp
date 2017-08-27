// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		<alloca.h>
#include		"lapin_private.h"

bool			bunny_collision_triangle_dot(const t_bunny_collision	*a,
						     const t_bunny_collision	*b)
{
  t_bunny_vertex_array	*arr = (t_bunny_vertex_array*)alloca(sizeof(arr->length) + 3 * sizeof(arr->vertex[0]));
  const t_bunny_triangle_collision *triangle = &a->triangle;
  size_t		i;

  for (i = 0, arr->length = 3; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = triangle->coord[i].x;
      arr->vertex[i].pos.y = triangle->coord[i].y;
    }
  return (bunny_triangle_collision_dot(arr, &b->dot.coord));
}

