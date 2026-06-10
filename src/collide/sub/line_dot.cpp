// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_line_dot(const t_bunny_collision	*a,
						 const t_bunny_collision	*b)
{
  const t_bunny_line_collision *line = &a->line;
  const t_bunny_dot_collision *dot = &b->dot;

  return (_bunny_collision_point_on_segment(line->coord[0], line->coord[1], dot->coord, 2.0));
}

