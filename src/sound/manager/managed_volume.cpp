// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		_bunny_managed_sound_volume(t_bunny_sound_manager	*_sm,
					    t_bunny_sound		*snd,
					    double			vol)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_sound_type>::iterator it;
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator itx;
  double	final;

  if ((it = sm->sound_to_type.find(snd)) == sm->sound_to_type.end())
    return (false);
  if ((itx = sm->sounds[it->second].find(snd)) == sm->sounds[it->second].end())
    return (false);
  itx->second.proper_volume = vol;
  final =
    (vol / 100.0)
    * (sm->general_volume / 100.0)
    * (sm->volumes[it->second] / 100.0)
    * 100.0;
  bunny_sound_volume(snd, final);
  return (true);
}

