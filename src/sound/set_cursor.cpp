// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

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

