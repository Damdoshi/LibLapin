// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_sound_pitch(t_bunny_sound		*sound,
					  double		pit)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (pit < 0)
    pit = 0;

  sound->pitch = pit;
  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setPitch(pit);
  else
    ((struct bunny_effect*)sound)->sound.setPitch(pit);
  scream_log_if("%p sound, %f pit", "sound", sound, pit);
}

