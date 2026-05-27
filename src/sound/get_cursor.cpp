// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_get_cursor
 * @doc-module sound
 * @doc-kind function
 * @doc-order 530
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the current playback cursor of a sound.
 * @param snd Sound to query.
 * @return-success Current cursor position in seconds.
 * @log May log in the "sound" domain.
 * @see bunny_sound_set_cursor, bunny_music_get_cursor
 *
 * @doc-lang fr
 * @brief Renvoie le curseur de lecture courant d'un son.
 * @param snd Son à consulter.
 * @return-success Position courante du curseur en secondes.
 * @log Peut écrire dans le domaine "sound".
 * @see bunny_sound_set_cursor, bunny_music_get_cursor
 */
double			bunny_sound_get_cursor(const t_bunny_sound	*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;
  double		f;

  if (*type == MUSIC)
    {
      struct bunny_music *mus = (struct bunny_music*)sound;

      f = mus->music.getPlayingOffset().asSeconds();
    }
  else
    {
      struct bunny_effect *snd = (struct bunny_effect*)sound;

      f = snd->sound->getPlayingOffset().asSeconds();
    }
  scream_log_if("%p -> %f", "sound", sound, f);
  return (f);
}

