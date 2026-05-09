// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_sprite_get_collision
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 285
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the collision shape associated with the current sprite frame.
 * @param sprite Sprite to inspect.
 * @return-success Returns a pointer to the current collision shape.
 * @return-failure Returns NULL if no collision shape is associated.
 * @see bunny_sprite_collide
 *
 * @doc-lang fr
 * @brief Renvoie la forme de collision associée à la frame courante du sprite.
 * @param sprite Sprite à inspecter.
 * @return-success Renvoie un pointeur vers la forme de collision courante.
 * @return-failure Renvoie NULL si aucune forme de collision n'est associée.
 * @see bunny_sprite_collide
 */
const t_bunny_collision_shapes *bunny_sprite_get_collision(const t_bunny_sprite	*spr)
{
  struct bunny_sprite	&sprite = *(struct bunny_sprite*)spr;
  t_bunny_animation	*anim;
  int			id;

  if (sprite.current_animation == -1)
    return (NULL);
  if (sprite.collision_shapes == NULL || sprite.nbr_collision == 0)
    return (NULL);
  if (sprite.animation == NULL)
    return (NULL);
  if ((anim = &sprite.animation[sprite.current_animation]) == NULL)
    return (NULL);
  if (anim->collision_shapes == NULL)
    return (NULL);
  id = anim->collision_shapes[sprite.current_frame];
  if (id == -1)
    return (NULL);
  return (&sprite.collision_shapes[id]);
}

