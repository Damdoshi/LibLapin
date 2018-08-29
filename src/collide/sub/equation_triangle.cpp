// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_equation_triangle(const t_bunny_collision	*a,
						  const t_bunny_collision	*b)
{
  const t_bunny_triangle_collision *triangle = &b->triangle;
  t_bunny_dot_collision dot;

  dot.type = BCT_DOT;
  dot.coord = triangle->coord[0];
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord = triangle->coord[1];
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  dot.coord = triangle->coord[2];
  if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
    return (true);

  return (false);
}

