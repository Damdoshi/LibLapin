// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_stabilize_headtrack(const t_bunny_area	*prev,
						  t_bunny_area		*cur,
						  double		speed)
{
  bunny_smooth_move((const t_bunny_position*)prev, (t_bunny_position*)cur, speed);
}

