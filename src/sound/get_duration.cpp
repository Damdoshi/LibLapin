// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_get_duration
 * @doc-module sound
 * @doc-kind function
 * @doc-order 540
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the duration of a sound.
 * @param snd Sound to query.
 * @return-success Duration in seconds.
 * @log May log in the "sound" domain.
 * @see bunny_sound_get_cursor
 *
 * @doc-lang fr
 * @brief Renvoie la durée d'un son.
 * @param snd Son à consulter.
 * @return-success Durée en secondes.
 * @log Peut écrire dans le domaine "sound".
 * @see bunny_sound_get_cursor
 */
double			bunny_sound_get_duration(const t_bunny_sound	*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;
  double		f;

  if (*type == MUSIC)
    {
      struct bunny_music *mus = (struct bunny_music*)sound;

      f = mus->music.getDuration().asSeconds();
    }
  else
    {
      struct bunny_effect *snd = (struct bunny_effect*)sound;

      f = snd->effect->getDuration().asSeconds();
    }
  scream_log_if("%p -> %f", "sound", sound, f);
  return (f);
}

