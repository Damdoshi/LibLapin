// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_quad_circle(const t_bunny_collision	*a,
					    const t_bunny_collision	*b)
{
  t_bunny_vertex_array *arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 4 * sizeof(arr->vertex[0]));
  const t_bunny_quad_collision *quad = &a->quad;
  const t_bunny_circle_collision *circle = &b->circle;
  t_bunny_accurate_position tmp;
  size_t 	i;

  for (i = 0, arr->length = 4; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = quad->coord[i].x;
      arr->vertex[i].pos.y = quad->coord[i].y;
    }
  for (i = 0; _get_point_on_circle(&circle->coord, circle->radius, i, &tmp); ++i)
    if (bunny_quad_collision_dot(arr, &tmp))
      return (true);
  return (false);
}

