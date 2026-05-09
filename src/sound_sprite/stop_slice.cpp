// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_sound_sprite_stop_slice
 * @doc-kind function
 * @doc-module sound_sprite
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Stops the currently played slice of a sound sprite.
 * @param sprite Sound sprite.
 * @return-success Returns true if playback was stopped.
 * @return-failure Returns false on failure.
 * @see bunny_sound_sprite_play_slice
 *
 * @doc-lang fr
 * @brief Arrête la tranche actuellement jouée d’un sound sprite.
 * @param sprite Sound sprite.
 * @return-success Renvoie true si la lecture a été arrêtée.
 * @return-failure Renvoie false en cas d’échec.
 * @see bunny_sound_sprite_play_slice
 */
bool		bunny_sound_sprite_stop_slice(t_bunny_sound_sprite	*sprite)
{
  struct bunny_music *music = (struct bunny_music*)sprite;

  if (sprite->last_played_slice == NULL)
    return (false);
  if (music->sound_manager)
    bunny_sound_manager_stop_music((t_bunny_sound_manager*)music->sound_manager, sprite->track);
  else
    bunny_sound_stop(&sprite->soundset.sound);
  *((t_bunny_sound_slice**)&sprite->last_played_slice) = NULL;
  *(t_bunny_music_track*)&sprite->track = BST_LAST_TRACK;
  return (true);
}

