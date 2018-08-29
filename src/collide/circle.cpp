// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

#define		PATTERN		"%p a, %p b, %f radius -> %s"

bool		bunny_circle_collision_dot(const t_bunny_accurate_position	*a,
					   const t_bunny_accurate_position	*b,
					   double				r)
{
  double	va, vb;

  va = b->x - a->x;
  vb = b->y - a->y;
  if (va * va + vb * vb < r * r)
    {
      scream_log_if(PATTERN, "collision", a, b, r, "true");
      return (true);
    }
  scream_log_if(PATTERN, "collision", a, b, r, "false");
  return (false);
}

