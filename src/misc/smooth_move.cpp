// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_smooth_move(const t_bunny_position	*target,
					  t_bunny_position		*current,
					  double			speed)
{
  t_bunny_position	res;

  res.x = speed * (target->x - current->x) + current->x;
  res.y = speed * (target->y - current->y) + current->y;
  current->x = res.x;
  current->y = res.y;
  scream_log_if("%p (%d, %d) target, %p (%d, %d) current, %f speed",
		target, target->x, target->y,
		current, current->x, current->y,
		speed);
}

