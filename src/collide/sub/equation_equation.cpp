// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/*
** ax^2 + bx + c = dx^2 + ex + f
** (a - d)x^2 + (b - e)x + c - f = 0
*/

bool		bunny_collision_equation_equation(const t_bunny_collision	*_a,
						  const t_bunny_collision	*_b)
{
  const t_bunny_equation_collision *a = &_a->equation;
  const t_bunny_equation_collision *b = &_b->equation;
  t_bunny_dot_collision dot;
  double	ac, bc, cc, delta;

  if (bunny_collision_rectangle_rectangle(_a, _b) == false)
    return (false);

  ac = a->a - b->a;
  bc = a->b - b->b;
  cc = a->c - b->c;
  delta = bc * bc - 4 * ac * cc;
  if (delta < 0)
    return (false);

  dot.type = BCT_DOT;
  if (delta >= 0)
    {
      dot.coord.x = (-bc + sqrt(delta)) / (2 * ac);
      dot.coord.y = ac * dot.coord.x * dot.coord.x + bc * dot.coord.x + cc;
      if (bunny_collision_rectangle_dot(_a, (t_bunny_collision*)&dot) &&
	  bunny_collision_rectangle_dot(_b, (t_bunny_collision*)&dot))
	return (true);
    }
  if (delta > 0.05)
    {
      dot.coord.x = (-bc - sqrt(delta)) / (2 * ac);
      dot.coord.y = ac * dot.coord.x * dot.coord.x + bc * dot.coord.x + cc;
      if (bunny_collision_rectangle_dot(_a, (t_bunny_collision*)&dot) &&
	  bunny_collision_rectangle_dot(_b, (t_bunny_collision*)&dot))
	return (true);
    }
  return (false);
}

