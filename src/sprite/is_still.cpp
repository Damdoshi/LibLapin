// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_sprite_is_still
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 200
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Checks whether the current sprite animation has reached a still state.
 * @param sprite Sprite to inspect.
 * @return-success Returns true if the animation is considered finished or still.
 * @return-failure Returns false while animation is still progressing.
 * @see bunny_sprite_stop_repeat
 *
 * @doc-lang fr
 * @brief Vérifie si l'animation courante du sprite a atteint un état immobile.
 * @param sprite Sprite à inspecter.
 * @return-success Renvoie true si l'animation est considérée terminée ou immobile.
 * @return-failure Renvoie false tant que l'animation progresse encore.
 * @see bunny_sprite_stop_repeat
 */
bool			bunny_sprite_is_still(t_bunny_sprite		*spr)
{
  return (spr->current_animation == -1);
}

