// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_volume
 * @doc-module sound
 * @doc-kind function
 * @doc-order 260
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Sets the volume of a sound.
 * @description The value is clamped between 0 and 100. Use bunny_managed_sound_volume for managed sounds.
 * @param sound Sound to modify.
 * @param volume New volume.
 * @log May log in the "sound" domain.
 * @see bunny_managed_sound_volume, bunny_sound_pitch
 *
 * @doc-lang fr
 * @brief Définit le volume d'un son.
 * @description La valeur est bornée entre 0 et 100. Utilisez bunny_managed_sound_volume pour les sons gérés.
 * @param sound Son à modifier.
 * @param volume Nouveau volume.
 * @log Peut écrire dans le domaine "sound".
 * @see bunny_managed_sound_volume, bunny_sound_pitch
 */
void			bunny_sound_volume(t_bunny_sound	*sound,
					   double		vol)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (vol < 0)
    vol = 0;
  else if (vol > 100)
    vol = 100;

  sound->volume = vol;
  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setVolume(vol);
  else
    ((struct bunny_effect*)sound)->sound->setVolume(vol);
  scream_log_if("%p sound, %f volume", "sound", sound, vol);
}

