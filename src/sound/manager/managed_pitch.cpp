// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		_bunny_managed_sound_pitch(t_bunny_sound_manager	*_sm,
					   t_bunny_sound		*snd,
					   double			pit)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_sound_type>::iterator it;
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator itx;

  if ((it = sm->sound_to_type.find(snd)) == sm->sound_to_type.end())
    return (false);
  if ((itx = sm->sounds[it->second].find(snd)) == sm->sounds[it->second].end())
    return (false);
  itx->second.proper_pitch = pit;
  bunny_sound_pitch(snd, pit * sm->general_pitch * sm->pitches[it->second]);
  return (true);
}

