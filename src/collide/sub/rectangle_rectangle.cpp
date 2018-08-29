// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_rectangle_rectangle(const t_bunny_collision	*a,
						    const t_bunny_collision	*b)
{
  return
    (bunny_rectangular_collision
     ((t_bunny_accurate_area*)&a->rectangular.coord[0],
      (t_bunny_accurate_area*)&b->rectangular.coord[0]
      )
     );
}

