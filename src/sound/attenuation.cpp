// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_attenuation
 * @doc-module sound
 * @doc-kind function
 * @doc-order 430
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets how quickly a positioned sound fades with distance.
 * @param sound Sound to modify.
 * @param attenuation Attenuation factor, commonly between 0 and 10.
 * @log May log in the "ressource" and "sound" domains.
 * @see bunny_sound_position
 *
 * @doc-lang fr
 * @brief Définit la vitesse à laquelle un son positionné décroît avec la distance.
 * @param sound Son à modifier.
 * @param attenuation Facteur d'atténuation, généralement entre 0 et 10.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_sound_position
 */
void			bunny_sound_attenuation(t_bunny_sound		*sound,
						double			att)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  sound->attenuation = att;
  scream_log_if("%p sound, %f attenuation", "ressource,sound", sound, att);
  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setAttenuation(att);
  else
    ((struct bunny_effect*)sound)->sound->setAttenuation(att);
}
