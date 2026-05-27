// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_pitch
 * @doc-module sound
 * @doc-kind function
 * @doc-order 280
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets the pitch and playback speed of a sound.
 * @param sound Sound to modify.
 * @param pitch Playback speed multiplier; 1 preserves the original speed.
 * @log May log in the "sound" domain.
 * @see bunny_managed_sound_pitch, bunny_sound_volume
 *
 * @doc-lang fr
 * @brief Définit la hauteur et la vitesse de lecture d'un son.
 * @param sound Son à modifier.
 * @param pitch Multiplicateur de vitesse de lecture ; 1 conserve la vitesse originale.
 * @log Peut écrire dans le domaine "sound".
 * @see bunny_managed_sound_pitch, bunny_sound_volume
 */
void			bunny_sound_pitch(t_bunny_sound		*sound,
					  double		pit)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (pit < 0)
    pit = 0;

  sound->pitch = pit;
  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setPitch(pit);
  else
    ((struct bunny_effect*)sound)->sound->setPitch(pit);
  scream_log_if("%p sound, %f pit", "sound", sound, pit);
}

