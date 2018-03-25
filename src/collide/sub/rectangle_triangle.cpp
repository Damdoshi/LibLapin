// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_rectangle_triangle(const t_bunny_collision	*a,
						   const t_bunny_collision	*b)
{
  const t_bunny_rectangular_collision *rectangle = &a->rectangular;
  const t_bunny_triangle_collision *triangle = &b->triangle;
  t_bunny_line_collision rline;
  t_bunny_line_collision tline;

  if (bunny_rectangular_collision_dot
      ((const t_bunny_accurate_area*)&rectangle->coord[0], &triangle->coord[0]))
    return (true);
  if (bunny_rectangular_collision_dot
      ((const t_bunny_accurate_area*)&rectangle->coord[0], &triangle->coord[1]))
    return (true);
  if (bunny_rectangular_collision_dot
      ((const t_bunny_accurate_area*)&rectangle->coord[0], &triangle->coord[2]))
    return (true);

  rline.intermediate_points = 0;
  tline.intermediate_points = 0;

  ///
  rline.coord[0].x = rectangle->coord[0].x;
  rline.coord[0].y = rectangle->coord[0].y;
  rline.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[1].y = rectangle->coord[0].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  rline.coord[0].x = rectangle->coord[0].x;
  rline.coord[0].y = rectangle->coord[0].y + rectangle->coord[1].y;
  rline.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  rline.coord[0].x = rectangle->coord[0].x;
  rline.coord[0].y = rectangle->coord[0].y;
  rline.coord[1].x = rectangle->coord[0].x;
  rline.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  rline.coord[0].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[0].y = rectangle->coord[0].y;
  rline.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  rline.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;

  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[1];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[1];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);
  tline.coord[0] = triangle->coord[0];
  tline.coord[1] = triangle->coord[2];
  if (bunny_collision_line_line((t_bunny_collision*)&rline, (t_bunny_collision*)&tline))
    return (true);

  return (false);
}

