// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	<alloca.h>
#include	"lapin_private.h"

bool		bunny_collision_equation_circle(const t_bunny_collision	*a,
						const t_bunny_collision	*b)
{
  const t_bunny_circle_collision *circle = &b->circle;
  t_bunny_dot_collision dot;
  int		i;

  dot.type = BCT_DOT;
  for (i = 0; _get_point_on_circle(&circle->coord, circle->radius, i, &dot.coord); ++i)
    if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
      return (true);
  return (false);
}

