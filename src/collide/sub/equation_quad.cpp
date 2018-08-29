// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_equation_quad(const t_bunny_collision	*a,
					      const t_bunny_collision	*b)
{
  const t_bunny_quad_collision *quad = &b->quad;
  t_bunny_dot_collision dot;

  dot.type = BCT_DOT;
  dot.coord.x = quad->coord[0].x;
  dot.coord.y = quad->coord[0].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord.x = quad->coord[1].x;
  dot.coord.y = quad->coord[1].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord.x = quad->coord[2].x;
  dot.coord.y = quad->coord[2].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord.x = quad->coord[3].x;
  dot.coord.y = quad->coord[3].y;
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  return (false);
}

