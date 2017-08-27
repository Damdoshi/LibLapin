// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_circle_circle(const t_bunny_collision	*a,
					      const t_bunny_collision	*b)
{
  return (bunny_circle_collision
	  (&a->circle.coord, a->circle.radius, &b->circle.coord, b->circle.radius));
}
