// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		_bunny_sound_manager_add(t_bunny_sound_manager	*_sm,
					 t_bunny_sound		*snd,
					 t_bunny_sound_type	typ)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_sound_type>::iterator it;
  t_bunny_managed_sound ms;

  if (typ < 0 || typ >= BST_LAST_SOUND_TYPE)
    return (false);
  if ((it = sm->sound_to_type.find(snd)) != sm->sound_to_type.end())
    {
      if (it->second == typ)
	return (true);
      return (false);
    }
  ms.proper_volume = snd->volume;
  ms.proper_pitch = snd->pitch;
  sm->sounds[typ][snd] = ms;
  return (true);
}

