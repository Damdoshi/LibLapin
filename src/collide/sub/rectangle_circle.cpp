// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_rectangle_circle(const t_bunny_collision	*a,
						 const t_bunny_collision	*b)
{
  const t_bunny_rectangular_collision *rectangle = &a->rectangular;
  const t_bunny_circle_collision *circle = &b->circle;
  t_bunny_accurate_position tmp;
  int		i;

  for (i = 0; _get_point_on_circle(&circle->coord, circle->radius, i, &tmp); ++i)
    if (bunny_rectangular_collision_dot((t_bunny_accurate_area*)&rectangle->coord[0], &tmp))
      return (true);
  return (false);
}

