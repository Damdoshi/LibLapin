// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/*

int IntersectionPlanCercleDroite(float A[2], float B[2], float C[2], float Rayon)
{
    float Alpha, Beta, Gamma, Delta;

    Alpha = (B[0] - A[0]) * (B[0] - A[0]) + (B[1] - A[1]) * (B[1] - A[1]);
    Beta  = 2 * ((B[0] - A[0]) * (A[0] - C[0]) + (B[1] - A[1]) * (A[1] - C[1]));
    Gamma = A[0] * A[0] + A[1] * A[1] + C[0] * C[0] + C[1] * C[1] - 2 * (A[0] * C[0] + A[1] * C[1]) - Rayon * Rayon;

    return (Beta * Beta - 4 * Alpha * Gamma) >= 0;
}


**
*/

bool			_test_interval(const t_bunny_line_collision		*line,
				       double					x,
				       double					y)
{
  if (line->coord[0].x < line->coord[1].x)
    {
      if (line->coord[0].x > x || line->coord[1].x < x)
	return (false);
    }
  else
    {
      if (line->coord[0].x < x || line->coord[1].x > x)
	return (false);
    }
  if (line->coord[0].y < line->coord[1].y)
    {
      if (line->coord[0].y > y || line->coord[1].y < y)
	return (false);
    }
  else
    {
      if (line->coord[0].y < y || line->coord[1].y > y)
	return (false);
    }
  return (true);
}

bool			bunny_collision_line_circle(const t_bunny_collision	*_a,
						    const t_bunny_collision	*_b)
{
  const t_bunny_line_collision *line = &_a->line;
  const t_bunny_circle_collision *circle = &_b->circle;
  double		xoff, yoff;
  double		a, b, c;
  double		delta;
  double		res;
  double		coef;
  double		offset;

  xoff = line->coord[1].x - line->coord[0].x;
  yoff = line->coord[1].y - line->coord[0].y;

  a = xoff * xoff + yoff * yoff;
  b = 2 * (xoff * (line->coord[0].x - circle->coord.x)
	   + yoff * (line->coord[0].y - circle->coord.y));
  c = pow(line->coord[0].x - circle->coord.x, 2)
    + pow(line->coord[0].y - circle->coord.y, 2)
    - pow(circle->radius, 2)
    ;

  if ((delta = b * b - 4 * a * c) < 0)
    return (false);
  coef = (line->coord[1].y - line->coord[0].y)
    / (line->coord[1].x - line->coord[0].x)
    ;
  offset = -line->coord[0].x * coef + line->coord[0].y;

  if (delta < 0.001)
    {
      res = -b / (2 * a);
      return (_test_interval(line, res, res * coef + offset));
    }
  delta = sqrt(delta);
  a *= 2;
  res = (-b + delta) / a + line->coord[0].x;
  if (_test_interval(line, res, res * coef + offset))
    return (true);
  res = (-b - delta) / a + line->coord[0].x;
  return (_test_interval(line, res, res * coef + offset));
}
