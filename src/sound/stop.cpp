// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_stop
 * @doc-module sound
 * @doc-kind function
 * @doc-order 490
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Stops a sound and clears its paused state.
 * @param sound Sound to stop.
 * @log May log in the "ressource" and "sound" domains.
 * @see bunny_sound_play, bunny_sound_pause
 *
 * @doc-lang fr
 * @brief Arrête un son et retire son état de pause.
 * @param sound Son à arrêter.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_sound_play, bunny_sound_pause
 */
void			bunny_sound_stop(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  *((bool*)&sound->pause) = false;
  *((bool*)&sound->playing) = false;
  if (*type == MUSIC)
    {
      struct bunny_music *snd = (struct bunny_music*)sound;

      snd->music.setPlayingOffset(sf::Time::Zero);
      snd->music.stop();
      snd->last_played_slice = NULL;
      snd->track = BST_LAST_TRACK;
      if (snd->trap)
	{
	  bunny_delete_trap(snd->trap);
	  snd->trap = NULL;
	}
    }
  else
    ((struct bunny_effect*)sound)->sound->stop();
  scream_log_if("%p", "ressource,sound", sound);
}

