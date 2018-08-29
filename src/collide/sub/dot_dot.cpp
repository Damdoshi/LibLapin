// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_dot_dot(const t_bunny_collision	*a,
					const t_bunny_collision	*b)
{
  return (bunny_circle_collision_dot(&a->dot.coord, &b->dot.coord, 1));
}
