// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_sprite_stop_repeat
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 300
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Stops the current animation from repeating after its current cycle.
 * @param sprite Sprite to update.
 * @see bunny_sprite_is_still
 *
 * @doc-lang fr
 * @brief Empêche l'animation courante de se répéter après son cycle courant.
 * @param sprite Sprite à mettre à jour.
 * @see bunny_sprite_is_still
 */
void			bunny_sprite_stop_repeat(t_bunny_sprite	*spr)
{
  spr->stop_repeat = true;
}

