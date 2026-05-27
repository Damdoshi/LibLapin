// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_quad_quad(const t_bunny_collision	*a,
					  const t_bunny_collision	*b)
{
  t_bunny_vertex_array *arra = (t_bunny_vertex_array*)bunny_alloca(sizeof(arra->length) + 4 * sizeof(arra->vertex[0]));
  t_bunny_vertex_array *arrb = (t_bunny_vertex_array*)bunny_alloca(sizeof(arrb->length) + 4 * sizeof(arrb->vertex[0]));
  const t_bunny_quad_collision *aquad = &a->quad;
  const t_bunny_quad_collision *bquad = &b->quad;
  size_t	i;
  size_t	j;

  for (i = 0, arra->length = arrb->length = 4; i < 4; ++i)
    {
      arra->vertex[i].pos.x = aquad->coord[i].x;
      arra->vertex[i].pos.y = aquad->coord[i].y;
      arrb->vertex[i].pos.x = bquad->coord[i].x;
      arrb->vertex[i].pos.y = bquad->coord[i].y;
    }

  for (i = 0; i < 4; ++i)
    {
      if (bunny_quad_collision_dot(arrb, &aquad->coord[i]))
	goto collide;
      if (bunny_quad_collision_dot(arra, &bquad->coord[i]))
	goto collide;
    }

  for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
      if (_bunny_collision_segment_intersection
	  (aquad->coord[i], aquad->coord[(i + 1) % 4],
	   bquad->coord[j], bquad->coord[(j + 1) % 4]))
	goto collide;

  bunny_freea(arra);
  bunny_freea(arrb);
  return (false);

 collide:
  bunny_freea(arra);
  bunny_freea(arrb);
  return (true);
}
