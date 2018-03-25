// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_equation_line(const t_bunny_collision	*a,
					      const t_bunny_collision	*b)
{
  const t_bunny_line_collision *line = &b->line;
  t_bunny_dot_collision dot;
  t_bunny_accurate_position pos;
  int		i;

  dot.type = BCT_DOT;
  pos.x = (line->coord[1].x - line->coord[0].x) / (line->intermediate_points + 1);
  pos.y = (line->coord[1].x - line->coord[0].y) / (line->intermediate_points + 1);
  dot.coord = line->coord[0];
  for (i = 0; i < line->intermediate_points + 2; ++i)
    if (bunny_collision_equation_dot(&a->equation, &dot).radian >= 0)
      return (true);
    else
      {
	dot.coord.x += pos.x;
	dot.coord.y += pos.y;
      }
  return (false);
}

