// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_sound_manager_play_music(t_bunny_sound_manager	*_sm,
					       t_bunny_music		*_snd,
					       t_bunny_music_track	n)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  t_bunny_sound	*snd = (t_bunny_sound*)_snd;
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator it;

  if ((it = sm->sounds[BST_MUSIC].find(snd)) == sm->sounds[BST_MUSIC].end())
    return (false);
  if (n == BST_ALL)
    {
      bunny_sound_manager_stop_music(_sm, n);
      n = BST_TRACK_01;
    }
  else if (sm->current_music[n] != NULL)
    {
      if (sm->current_music[n] == snd)
	return (true);
      bunny_sound_stop(sm->current_music[n]);
    }
  sm->current_music[n] = it->first;
  bunny_sound_play(it->first);
  return (true);
}
