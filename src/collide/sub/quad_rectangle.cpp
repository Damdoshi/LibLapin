// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_quad_rectangle(const t_bunny_collision	*a,
					       const t_bunny_collision	*b)
{
  t_bunny_vertex_array *qarr = (t_bunny_vertex_array*)bunny_alloca(sizeof(qarr->length) + 4 * sizeof(qarr->vertex[0]));
  const t_bunny_quad_collision *quad = &a->quad;
  const t_bunny_rectangular_collision *rectangle = &b->rectangular;
  t_bunny_accurate_position corner[4];
  size_t	i;
  size_t	j;

  corner[0] = rectangle->coord[0];
  corner[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  corner[1].y = rectangle->coord[0].y;
  corner[2].x = rectangle->coord[0].x + rectangle->coord[1].x;
  corner[2].y = rectangle->coord[0].y + rectangle->coord[1].y;
  corner[3].x = rectangle->coord[0].x;
  corner[3].y = rectangle->coord[0].y + rectangle->coord[1].y;

  for (i = 0, qarr->length = 4; i < 4; ++i)
    {
      qarr->vertex[i].pos.x = quad->coord[i].x;
      qarr->vertex[i].pos.y = quad->coord[i].y;
    }

  for (i = 0; i < 4; ++i)
    if (bunny_rectangular_collision_dot
	((const t_bunny_accurate_area*)&rectangle->coord[0], &quad->coord[i]))
      goto collide;
  for (i = 0; i < 4; ++i)
    if (bunny_quad_collision_dot(qarr, &corner[i]))
      goto collide;
  for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
      if (_bunny_collision_segment_intersection
	  (quad->coord[i], quad->coord[(i + 1) % 4], corner[j], corner[(j + 1) % 4]))
	goto collide;

  bunny_freea(qarr);
  return (false);

 collide:
  bunny_freea(qarr);
  return (true);
}
