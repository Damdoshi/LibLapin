// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_set_cursor
 * @doc-module sound
 * @doc-kind function
 * @doc-order 510
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Moves the playback cursor of a sound.
 * @param snd Sound whose cursor must be moved.
 * @param secs New cursor position in seconds.
 * @log May log in the "ressource" and "sound" domains.
 * @see bunny_sound_get_cursor, bunny_sound_get_duration
 *
 * @doc-lang fr
 * @brief Déplace le curseur de lecture d'un son.
 * @param snd Son dont le curseur doit être déplacé.
 * @param secs Nouvelle position du curseur en secondes.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_sound_get_cursor, bunny_sound_get_duration
 */
void			bunny_sound_set_cursor(t_bunny_sound		*sound,
					       double			s)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  bunny_sound_stop(sound);
  bunny_sound_play(sound);
  if (*type == MUSIC)
    {
      struct bunny_music *mus = (struct bunny_music*)sound;

      mus->music.setPlayingOffset(sf::seconds(s));
    }
  else
    {
      struct bunny_effect *snd = (struct bunny_effect*)sound;

      snd->sound->setPlayingOffset(sf::seconds(s));
    }
  bunny_sound_pause(sound);
  scream_log_if("%p -> ", "ressource,sound", sound);
}

