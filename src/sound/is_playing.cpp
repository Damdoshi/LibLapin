// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_is_playing
 * @doc-module sound
 * @doc-kind function
 * @doc-order 545
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Indicates whether a sound is currently playing.
 * @param snd Sound to query.
 * @return-success true if the sound is playing, false otherwise.
 * @see bunny_sound_play, bunny_sound_pause, bunny_sound_stop
 *
 * @doc-lang fr
 * @brief Indique si un son est actuellement en cours de lecture.
 * @param snd Son à consulter.
 * @return-success true si le son est en cours de lecture, false sinon.
 * @see bunny_sound_play, bunny_sound_pause, bunny_sound_stop
 */
bool			bunny_sound_is_playing(const t_bunny_sound	*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (*type == MUSIC)
    {
      struct bunny_music *mus = (struct bunny_music*)sound;

      return (mus->playing = mus->music.getStatus() == sf::SoundSource::Status::Playing);
    }
  struct bunny_effect *snd = (struct bunny_effect*)sound;

  return (snd->playing = snd->sound->getStatus() == sf::SoundSource::Status::Playing);
}

