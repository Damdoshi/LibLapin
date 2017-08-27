// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	<alloca.h>
#include	"lapin_private.h"

bool		bunny_collision_equation_rectangle(const t_bunny_collision	*a,
						   const t_bunny_collision	*b)
{
  const t_bunny_rectangular_collision *rectangular = &b->rectangular;
  t_bunny_dot_collision dot;

  dot.type = BCT_DOT;
  dot.coord.x = rectangular->coord[0].x;
  dot.coord.y = rectangular->coord[0].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord.x = rectangular->coord[0].x + rectangular->coord[1].x;
  dot.coord.y = rectangular->coord[0].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord.x = rectangular->coord[0].x;
  dot.coord.y = rectangular->coord[0].y + rectangular->coord[1].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord.x = rectangular->coord[0].x + rectangular->coord[1].x;
  dot.coord.y = rectangular->coord[0].y + rectangular->coord[1].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  return (false);
}

