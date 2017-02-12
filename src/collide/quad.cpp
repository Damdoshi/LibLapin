// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		<alloca.h>
#include		"lapin_private.h"

bool			bunny_quad_collision_dot(const t_bunny_vertex_array		*v4,
						 const t_bunny_accurate_position	*dot)
{
  t_bunny_vertex_array	*t1 = (t_bunny_vertex_array*)alloca(sizeof(*t1) + 3 * sizeof(t1->vertex[0]));
  t_bunny_vertex_array	*t2 = (t_bunny_vertex_array*)alloca(sizeof(*t1) + 3 * sizeof(t1->vertex[0]));

  if (v4->length != 4)
    return (false);
  t1->length = 3;
  t1->vertex[0].pos.x = v4->vertex[0].pos.x;
  t1->vertex[0].pos.y = v4->vertex[0].pos.y;
  t1->vertex[1].pos.x = v4->vertex[1].pos.x;
  t1->vertex[1].pos.y = v4->vertex[1].pos.y;
  t1->vertex[2].pos.x = v4->vertex[2].pos.x;
  t1->vertex[2].pos.y = v4->vertex[2].pos.y;
  if (bunny_triangle_collision_dot(t1, dot))
    return (true);

  t2->length = 3;
  t2->vertex[0].pos.x = v4->vertex[0].pos.x;
  t2->vertex[0].pos.y = v4->vertex[0].pos.y;
  t2->vertex[1].pos.x = v4->vertex[2].pos.x;
  t2->vertex[1].pos.y = v4->vertex[2].pos.y;
  t2->vertex[2].pos.x = v4->vertex[3].pos.x;
  t2->vertex[2].pos.y = v4->vertex[3].pos.y;
  return (bunny_triangle_collision_dot(t2, dot));
}

