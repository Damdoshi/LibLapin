// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/*
** ax^2 + bx + c = dx^2 + ex + f
** (a - d)x^2 + (b - e)x + c - f = 0
*/

static bool	test_root(const t_bunny_collision		*_a,
			  const t_bunny_collision		*_b,
			  double				x)
{
  const t_bunny_equation_collision *a = &_a->equation;
  t_bunny_dot_collision dot;

  dot.type = BCT_DOT;
  dot.coord.x = x;
  dot.coord.y = a->a * x * x + a->b * x + a->c;
  return (bunny_collision_rectangle_dot(_a, (t_bunny_collision*)&dot) &&
	  bunny_collision_rectangle_dot(_b, (t_bunny_collision*)&dot));
}

bool		bunny_collision_equation_equation(const t_bunny_collision	*_a,
						  const t_bunny_collision	*_b)
{
  const t_bunny_equation_collision *a = &_a->equation;
  const t_bunny_equation_collision *b = &_b->equation;
  double	ac, bc, cc, delta;

  if (bunny_collision_rectangle_rectangle(_a, _b) == false)
    return (false);

  ac = a->a - b->a;
  bc = a->b - b->b;
  cc = a->c - b->c;
  if (fabs(ac) < 0.000001)
    {
      if (fabs(bc) < 0.000001)
	return (fabs(cc) < 0.000001);
      return (test_root(_a, _b, -cc / bc));
    }
  delta = bc * bc - 4 * ac * cc;
  if (delta < 0)
    return (false);
  if (test_root(_a, _b, (-bc + sqrt(delta)) / (2 * ac)))
    return (true);
  if (delta > 0.000001 && test_root(_a, _b, (-bc - sqrt(delta)) / (2 * ac)))
    return (true);
  return (false);
}

