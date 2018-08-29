// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_circle_dot(const t_bunny_collision	*a,
					   const t_bunny_collision	*b)
{
  return (bunny_circle_collision_dot
	  (&a->circle.coord, &b->dot.coord, a->circle.radius));
}
