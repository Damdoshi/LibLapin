// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/*
** ax + b = c
** ax + b - c = 0
** ax - c = -b
** -ax + c = b
*/

bool			bunny_collision_line_dot(const t_bunny_collision	*a,
						 const t_bunny_collision	*b)
{
  const t_bunny_line_collision *line = &a->line;
  const t_bunny_dot_collision *dot = &b->dot;
  double		coef;
  double		offset;

  coef = (line->coord[1].y - line->coord[0].y) / (line->coord[1].x - line->coord[0].x);
  offset = -line->coord[0].x * coef + line->coord[0].y;

  if ((int)(line->coord[0].x - line->coord[1].x) == 0)
    {
      if (line->coord[0].y < line->coord[1].y)
	{
	  if (line->coord[0].y > dot->coord.y || line->coord[1].y < dot->coord.y)
	    return (false);
	}
      else
	{
	  if (line->coord[0].y < dot->coord.y || line->coord[1].y > dot->coord.y)
	    return (false);
	}
    }
  else if (line->coord[0].x < line->coord[1].x)
    {
      if (line->coord[0].x > dot->coord.x || line->coord[1].x < dot->coord.x)
	return (false);
    }
  else
    {
      if (line->coord[0].x < dot->coord.x || line->coord[1].x > dot->coord.x)
	return (false);
    }

  return (abs((dot->coord.x * coef + offset) - dot->coord.y) < 2);
}

