// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_rectangle_dot(const t_bunny_collision	*a,
						      const t_bunny_collision	*b)
{
  return
    (bunny_rectangular_collision_dot
     ((t_bunny_accurate_area*)&a->rectangular.coord[0],
      &b->dot.coord));
}

