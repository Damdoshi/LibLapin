// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_sound_pause(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (sound->playing == false)
    return ;
  *((bool*)&sound->pause) = true;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.pause();
  else
    ((struct bunny_effect*)sound)->sound->pause();
  scream_log_if("%p", "ressource,sound", sound);
}

