// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		_bunny_sound_manager_remove(t_bunny_sound_manager	*_sm,
					    t_bunny_sound		*snd)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_sound_type>::iterator it;
  int		i;

  if ((it = sm->sound_to_type.find(snd)) == sm->sound_to_type.end())
    return ;
  sm->sounds[it->second].erase(snd);
  sm->sound_to_type.erase(it);
  for (i = 0; i < BST_LAST_TRACK; ++i)
    if (sm->current_music[i] == snd)
      {
	sm->current_music[i] = NULL;
	bunny_sound_stop(snd);
      }
}

