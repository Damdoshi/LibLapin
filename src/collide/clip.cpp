// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_clip_collision_dot(const t_bunny_clipable			*elem,
						 const t_bunny_accurate_position	*pos)
{
  t_bunny_position	l, s;

  l.x = elem->position.x - elem->origin.x;
  l.y = elem->position.y - elem->origin.y;
  s.x = elem->clip_width * elem->scale.x;
  s.y = elem->clip_height * elem->scale.y;
  
  return (pos->x >= l.x && pos->x < l.x + s.x && pos->y >= l.y && pos->y < l.y + s.y);
}

bool			bunny_clip_collision(const t_bunny_clipable			*a,
					     const t_bunny_clipable			*b)
{
  t_bunny_position	al, as, bl, bs;

  al.x = a->position.x - a->origin.x;
  al.y = a->position.y - a->origin.y;
  as.x = a->clip_width * a->scale.x;
  as.y = a->clip_height * a->scale.y;

  bl.x = b->position.x - b->origin.x;
  bl.y = b->position.y - b->origin.y;
  bs.x = b->clip_width * b->scale.x;
  bs.y = b->clip_height * b->scale.y;

  return (al.x < bl.x + bs.x && al.x + as.x > bl.x && al.y < bl.y + bs.y && al.y + as.y > bl.y);
}

