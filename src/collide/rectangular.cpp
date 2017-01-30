// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_rectangular_collision_dot(const t_bunny_accurate_area	*elem,
							const t_bunny_accurate_position	*pos)
{
  return (pos->x >= elem->x && pos->x < elem->x + elem->w &&
	  pos->y >= elem->y && pos->y < elem->y + elem->h);
}

bool			bunny_rectangular_collision(const t_bunny_accurate_area		*a,
						    const t_bunny_accurate_area		*b)
{
  return (a->x < b->x + b->w && a->x + a->w > b->x &&
	  a->y < b->y + b->h && a->y + a->h > b->y);
}

