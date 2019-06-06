// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

const t_bunny_collision_shapes *bunny_sprite_get_collision(const t_bunny_sprite	*spr)
{
  struct bunny_sprite	&sprite = *(struct bunny_sprite*)spr;
  t_bunny_animation	*anim;
  int			id;

  if (sprite.current_animation == -1)
    return (NULL);
  if (sprite.collision_shapes == NULL || sprite.nbr_collision == 0)
    return (NULL);
  anim = &sprite.animation[sprite.current_animation];

  id = anim->collision_shapes[sprite.current_frame];
  if (id == -1)
    return (NULL);
  return (&sprite.collision_shapes[id]);
}

