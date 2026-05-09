// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_quad_triangle(const t_bunny_collision	*a,
					      const t_bunny_collision	*b)
{
  t_bunny_vertex_array *qarr = (t_bunny_vertex_array*)bunny_alloca(sizeof(qarr->length) + 4 * sizeof(qarr->vertex[0]));
  t_bunny_vertex_array *tarr = (t_bunny_vertex_array*)bunny_alloca(sizeof(tarr->length) + 3 * sizeof(tarr->vertex[0]));
  const t_bunny_quad_collision *quad = &a->quad;
  const t_bunny_triangle_collision *triangle = &b->triangle;
  size_t	i;
  size_t	j;

  for (i = 0, qarr->length = 4; i < 4; ++i)
    {
      qarr->vertex[i].pos.x = quad->coord[i].x;
      qarr->vertex[i].pos.y = quad->coord[i].y;
    }
  for (i = 0, tarr->length = 3; i < 3; ++i)
    {
      tarr->vertex[i].pos.x = triangle->coord[i].x;
      tarr->vertex[i].pos.y = triangle->coord[i].y;
    }

  for (i = 0; i < 3; ++i)
    if (bunny_quad_collision_dot(qarr, &triangle->coord[i]))
      goto collide;
  for (i = 0; i < 4; ++i)
    if (bunny_triangle_collision_dot(tarr, &quad->coord[i]))
      goto collide;
  for (i = 0; i < 4; ++i)
    for (j = 0; j < 3; ++j)
      if (_bunny_collision_segment_intersection
	  (quad->coord[i], quad->coord[(i + 1) % 4],
	   triangle->coord[j], triangle->coord[(j + 1) % 3]))
	goto collide;

  bunny_freea(qarr);
  bunny_freea(tarr);
  return (false);

 collide:
  bunny_freea(qarr);
  bunny_freea(tarr);
  return (true);
}
