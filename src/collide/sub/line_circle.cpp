// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_line_circle(const t_bunny_collision	*_a,
						    const t_bunny_collision	*_b)
{
  const t_bunny_line_collision *line = &_a->line;
  const t_bunny_circle_collision *circle = &_b->circle;
  double		rad = circle->radius;

  if (rad < 0)
    rad = -rad;
  return (_bunny_collision_point_segment_distance_square
	  (line->coord[0], line->coord[1], circle->coord) <= rad * rad);
}

