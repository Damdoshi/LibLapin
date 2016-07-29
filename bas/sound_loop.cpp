// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_sound_loop(t_bunny_sound		*sound,
					 bool			lop)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setLoop(lop);
  else
    ((struct bunny_effect*)sound)->sound.setLoop(lop);
}
