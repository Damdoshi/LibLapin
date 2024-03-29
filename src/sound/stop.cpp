// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_sound_stop(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  *((bool*)&sound->pause) = false;
  *((bool*)&sound->playing) = false;
  if (*type == MUSIC)
    {
      struct bunny_music *snd = (struct bunny_music*)sound;

      snd->music.setPlayingOffset(sf::Time::Zero);
      snd->music.stop();
      snd->last_played_slice = NULL;
      snd->track = BST_LAST_TRACK;
      if (snd->trap)
	{
	  bunny_delete_trap(snd->trap);
	  snd->trap = NULL;
	}
    }
  else
    ((struct bunny_effect*)sound)->sound->stop();
  scream_log_if("%p", "ressource,sound", sound);
}

