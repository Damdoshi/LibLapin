// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_rectangle_line(const t_bunny_collision	*a,
					       const t_bunny_collision	*b)
{
  const t_bunny_rectangular_collision *rectangle = &a->rectangular;
  const t_bunny_line_collision *line = &b->line;
  t_bunny_line_collision pos;

  if (bunny_rectangular_collision_dot
      ((t_bunny_accurate_area*)&rectangle->coord[0], &line->coord[0]))
    return (true);

  if (bunny_rectangular_collision_dot
      ((t_bunny_accurate_area*)&rectangle->coord[0], &line->coord[1]))
    return (true);

  pos.intermediate_points = 0;

  pos.coord[0].x = rectangle->coord[0].x;
  pos.coord[0].y = rectangle->coord[0].y;
  pos.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  pos.coord[1].y = rectangle->coord[0].y;
  if (bunny_collision_line_line((t_bunny_collision*)&pos, b))
    return (true);

  pos.coord[0].x = rectangle->coord[0].x;
  pos.coord[0].y = rectangle->coord[0].y + rectangle->coord[1].y;
  pos.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  pos.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;
  if (bunny_collision_line_line((t_bunny_collision*)&pos, b))
    return (true);

  pos.coord[0].x = rectangle->coord[0].x;
  pos.coord[0].y = rectangle->coord[0].y;
  pos.coord[1].x = rectangle->coord[0].x;
  pos.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;
  if (bunny_collision_line_line((t_bunny_collision*)&pos, b))
    return (true);

  pos.coord[0].x = rectangle->coord[0].x + rectangle->coord[1].x;
  pos.coord[0].y = rectangle->coord[0].y;
  pos.coord[1].x = rectangle->coord[0].x + rectangle->coord[1].x;
  pos.coord[1].y = rectangle->coord[0].y + rectangle->coord[1].y;
  if (bunny_collision_line_line((t_bunny_collision*)&pos, b))
    return (true);

  return (false);
}
