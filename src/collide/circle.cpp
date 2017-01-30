// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_circle_collision_dot(const t_bunny_accurate_position	*a,
						   const t_bunny_accurate_position	*b,
						   double				r)
{
  double		va, vb;

  va = b->x - a->x;
  vb = b->y - a->y;
  return (va * va + vb * vb < r * r);
}

