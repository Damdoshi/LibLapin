// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_sound_position(t_bunny_sound		*sound,
					     double			x,
					     double			y,
					     double			z)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setPosition(x, y, z);
  else
    ((struct bunny_effect*)sound)->sound.setPosition(x, y, z);
}
