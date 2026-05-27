// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_pause
 * @doc-module sound
 * @doc-kind function
 * @doc-order 470
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Pauses a playing sound.
 * @param sound Sound to pause.
 * @log May log in the "ressource" and "sound" domains.
 * @see bunny_sound_play, bunny_sound_stop
 *
 * @doc-lang fr
 * @brief Met un son en pause.
 * @param sound Son à mettre en pause.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_sound_play, bunny_sound_stop
 */
void			bunny_sound_pause(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (sound->playing == false)
    return ;
  *((bool*)&sound->pause) = true;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.pause();
  else
    ((struct bunny_effect*)sound)->sound->pause();
  scream_log_if("%p", "ressource,sound", sound);
}

