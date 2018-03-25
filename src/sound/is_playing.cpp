// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_sound_is_playing(const t_bunny_sound	*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (*type == MUSIC)
    {
      struct bunny_music *mus = (struct bunny_music*)sound;

      return (mus->playing = mus->music.getStatus() == sf::SoundSource::Playing);
    }
  struct bunny_effect *snd = (struct bunny_effect*)sound;

  return (snd->playing = snd->sound.getStatus() == sf::SoundSource::Playing);
}

