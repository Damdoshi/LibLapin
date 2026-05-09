// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_rectangle_triangle(const t_bunny_collision	*a,
						   const t_bunny_collision	*b)
{
  const t_bunny_rectangular_collision *rectangle = &a->rectangular;
  const t_bunny_triangle_collision *triangle = &b->triangle;
  t_bunny_vertex_array *tarr = (t_bunny_vertex_array*)bunny_alloca(sizeof(tarr->length) + 3 * sizeof(tarr->vertex[0]));
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
  for (i = 0, tarr->length = 3; i < 3; ++i)
    {
      tarr->vertex[i].pos.x = triangle->coord[i].x;
      tarr->vertex[i].pos.y = triangle->coord[i].y;
    }

  for (i = 0; i < 3; ++i)
    if (bunny_rectangular_collision_dot
	((const t_bunny_accurate_area*)&rectangle->coord[0], &triangle->coord[i]))
      goto collide;
  for (i = 0; i < 4; ++i)
    if (bunny_triangle_collision_dot(tarr, &corner[i]))
      goto collide;
  for (i = 0; i < 4; ++i)
    for (j = 0; j < 3; ++j)
      if (_bunny_collision_segment_intersection
	  (corner[i], corner[(i + 1) % 4],
	   triangle->coord[j], triangle->coord[(j + 1) % 3]))
	goto collide;

  bunny_freea(tarr);
  return (false);

 collide:
  bunny_freea(tarr);
  return (true);
}
