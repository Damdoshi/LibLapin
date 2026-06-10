// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_sprite_get_animation
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the hash of the current sprite animation.
 * @param sprite Sprite to inspect.
 * @return-success Returns the current animation hash.
 * @see bunny_sprite_animation_name
 *
 * @doc-lang fr
 * @brief Renvoie le hash de l'animation courante du sprite.
 * @param sprite Sprite à inspecter.
 * @return-success Renvoie le hash de l'animation courante.
 * @see bunny_sprite_animation_name
 */
uint64_t		bunny_sprite_get_animation(const t_bunny_sprite	*_sprite)
{
  t_bunny_sprite	*sprite = (t_bunny_sprite*)_sprite;

  return (sprite->current_animation_hash);
}

