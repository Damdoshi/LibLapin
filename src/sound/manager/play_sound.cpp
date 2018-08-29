// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_sound_manager_play_sound(t_bunny_sound_manager	*_sm,
					       t_bunny_effect		*_snd)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator it;
  std::map<t_bunny_sound*, t_bunny_sound_type>::iterator itx;
  t_bunny_sound	*snd = (t_bunny_sound*)_snd;

  if ((itx = sm->sound_to_type.find(snd)) == sm->sound_to_type.end())
    return (false);
  if ((it = sm->sounds[itx->second].find(snd)) == sm->sounds[itx->second].end())
    return (false);
  bunny_sound_play(it->first);
  return (true);
}
