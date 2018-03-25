// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

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

