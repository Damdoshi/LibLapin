// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_line_line(const t_bunny_collision	*a,
						  const t_bunny_collision	*b)
{
  const t_bunny_line_collision	*aline = &a->line;
  const t_bunny_line_collision	*bline = &b->line;

  return (_bunny_collision_segment_intersection
	  (aline->coord[0], aline->coord[1], bline->coord[0], bline->coord[1]));
}

