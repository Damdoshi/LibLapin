// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_sound_attenuation(t_bunny_sound		*sound,
						double			att)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setAttenuation(att);
  else
    ((struct bunny_effect*)sound)->sound.setAttenuation(att);
}
