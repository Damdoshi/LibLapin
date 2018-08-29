// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_stabilize_headtrack(const t_bunny_area	*prev,
						  t_bunny_area		*cur,
						  double		speed)
{
  scream_log_if("%p prev, %p cur, %f speed", "camera", prev, cur, speed);
  bunny_smooth_move((const t_bunny_position*)prev, (t_bunny_position*)cur, speed);
}

