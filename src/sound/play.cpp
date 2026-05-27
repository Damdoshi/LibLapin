// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_play
 * @doc-module sound
 * @doc-kind function
 * @doc-order 450
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Plays a sound.
 * @description Current sound attributes are applied before playback. If you edited t_bunny_effect.sample, call bunny_compute_effect first.
 * @param sound Sound to play.
 * @log May log in the "ressource" and "sound" domains.
 * @see bunny_sound_pause, bunny_sound_stop, bunny_compute_effect
 *
 * @doc-lang fr
 * @brief Joue un son.
 * @description Les attributs courants du son sont appliqués avant lecture. Si vous avez modifié t_bunny_effect.sample, appelez d'abord bunny_compute_effect.
 * @param sound Son à jouer.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_sound_pause, bunny_sound_stop, bunny_compute_effect
 */
void			bunny_sound_play(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  bunny_sound_volume(sound, sound->volume);
  bunny_sound_pitch(sound, sound->pitch);
  bunny_sound_loop(sound, sound->loop);
  bunny_sound_position
    (sound, sound->position[0], sound->position[1], sound->position[2]);
  bunny_sound_attenuation(sound, sound->attenuation);

  if (sound->pause)
    *((bool*)&sound->pause) = false;
  else
    *((bool*)&sound->playing) = true;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.play();
  else
    ((struct bunny_effect*)sound)->sound->play();
  scream_log_if("%p", "ressource,sound", sound);
}

