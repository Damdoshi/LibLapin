// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_sound_sprite_is_talking
 * @doc-kind function
 * @doc-module sound_sprite
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Reports whether the current slice is inside its active/talking duration.
 * @param sprite Sound sprite.
 * @return-success Returns true if the current playback time is inside the active part.
 * @return-failure Returns false otherwise.
 * @see t_bunny_sound_slice
 *
 * @doc-lang fr
 * @brief Indique si la tranche courante est dans sa durée active/parlée.
 * @param sprite Sound sprite.
 * @return-success Renvoie true si le temps de lecture courant est dans la partie active.
 * @return-failure Renvoie false sinon.
 * @see t_bunny_sound_slice
 */
bool		bunny_sound_sprite_is_talking(t_bunny_sound_sprite	*spr)
{
  if (spr->last_played_slice == NULL)
    return (false);
  double	cur = bunny_sound_get_cursor(&spr->soundset.sound);

  return (cur - spr->last_played_slice->index <=
	  spr->last_played_slice->active_duration
	  * spr->last_played_slice->sound.pitch);
}

