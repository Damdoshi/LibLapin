// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/*
** ax + b = cx + d
** ax - cx = d - b
** x * (a - c) = d - b
** x = (d - b) / (a - c)
*/

bool			bunny_collision_line_line(const t_bunny_collision	*a,
						  const t_bunny_collision	*b)
{
  const t_bunny_line_collision	*aline = &a->line;
  const t_bunny_line_collision	*bline = &b->line;
  double		acoef, bcoef;
  double		aoff, boff;
  double		x;

  acoef = (aline->coord[1].y - aline->coord[0].y) / (aline->coord[1].x - aline->coord[0].x);
  aoff = -aline->coord[0].x * acoef + aline->coord[0].y;

  bcoef = (bline->coord[1].y - bline->coord[0].y) / (bline->coord[1].x - bline->coord[0].x);
  boff = -bline->coord[0].x * bcoef + bline->coord[0].y;

  if (fabs(acoef - bcoef) < 0.001)
    return (false);
  x = (boff - aoff) / (bcoef - acoef);

  return
    (((aline->coord[0].x < aline->coord[1].x
       && x >= aline->coord[0].x
       && x <= aline->coord[1].x)
      ||
      (aline->coord[0].x > aline->coord[1].x
       && x <= aline->coord[0].x
       && x >= aline->coord[1].x)
      )
     &&
     ((bline->coord[0].x < bline->coord[1].x
       && x >= bline->coord[0].x
       && x <= bline->coord[1].x)
      ||
      (bline->coord[0].x > bline->coord[1].x
       && x <= bline->coord[0].x
       && x >= bline->coord[1].x)
      )
     );
}

