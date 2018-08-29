// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_quad_rectangle(const t_bunny_collision	*a,
					       const t_bunny_collision	*b)
{
  t_bunny_vertex_array *arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 4 * sizeof(arr->vertex[0]));
  const t_bunny_quad_collision *quad = &a->quad;
  const t_bunny_rectangular_collision *rectangle = &b->rectangular;
  t_bunny_line_collision rline;
  t_bunny_line_collision tline;
  t_bunny_accurate_position pos;
  size_t	i;

  for (i = 0, arr->length = 4; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = quad->coord[i].x;
      arr->vertex[i].pos.y = quad->coord[i].y;
    }

  if (bunny_rectangular_collision_dot
      ((const t_bunny_accurate_area*)&rectangle->coord[0], &quad->coord[0]))
    return (true);
  if (bunny_rectangular_collision_dot
      ((const t_bunny_accurate_area*)&rectangle->coord[0], &quad->coord[1]))
    return (true);
  if (bunny_rectangular_collision_dot
      ((const t_bunny_accurate_area*)&rectangle->coord[0], &quad->coord[2]))
    return (true);
  if (bunny_rectangular_collision_dot
      ((const t_bunny_accurate_area*)&rectangle->coord[0], &quad->coord[3]))
    return (true);

  pos = rectangle->coord[0];
  if (bunny_quad_collision_dot(arr, &pos))
    return (true);

  pos.x = rectangle->coord[0].x + rectangle->coord[1].x;
  pos.y = rectangle->coord[0].y;
  if (bunny_quad_collision_dot(arr, &pos))
    return (true);

  pos.x = rectangle->coord[0].x;
  pos.y = rectangle->coord[0].y + rectangle->coord[1].y;
  if (bunny_quad_collision_dot(arr, &pos))
    return (true);

  pos.x = rectangle->coord[0].x + rectangle->coord[1].x;
  pos.y = rectangle->coord[0].y + rectangle->coord[1].y;
  if (bunny_quad_collision_dot(arr, &pos))
    return (true);

  rline.intermediate_points = 0;
  tline.intermediate_points = 0;

  ///
  rline.coord[0].x = rectangle->coord[0].x;
  rline.coord[0].y = rectangle->coord[0].y;
  rline.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[1].y = rectangle->coord[0].y;
  
  tline.coord[0] = quad->coord[0];
  tline.coord[1] = quad->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[1];
  tline.coord[1] = quad->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[2];
  tline.coord[1] = quad->coord[3];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[3];
  tline.coord[1] = quad->coord[0];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  rline.coord[0].x = rectangle->coord[0].x;
  rline.coord[0].y = rectangle->coord[0].y + rectangle->coord[1].y;
  rline.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;

  tline.coord[0] = quad->coord[0];
  tline.coord[1] = quad->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[1];
  tline.coord[1] = quad->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[2];
  tline.coord[1] = quad->coord[3];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[3];
  tline.coord[1] = quad->coord[0];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  rline.coord[0].x = rectangle->coord[0].x;
  rline.coord[0].y = rectangle->coord[0].y;
  rline.coord[1].x = rectangle->coord[0].x;
  rline.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;

  tline.coord[0] = quad->coord[0];
  tline.coord[1] = quad->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[1];
  tline.coord[1] = quad->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[2];
  tline.coord[1] = quad->coord[3];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[3];
  tline.coord[1] = quad->coord[0];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  rline.coord[0].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[0].y = rectangle->coord[0].y;
  rline.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;

  tline.coord[0] = quad->coord[0];
  tline.coord[1] = quad->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[1];
  tline.coord[1] = quad->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[2];
  tline.coord[1] = quad->coord[3];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = quad->coord[3];
  tline.coord[1] = quad->coord[0];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  return (false);
}
