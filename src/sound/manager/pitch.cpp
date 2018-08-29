// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		bunny_sound_manager_pitch(t_bunny_sound_manager		*_sm,
					  t_bunny_sound_type		typ,
					  double			pit)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_managed_sound> &map = sm->sounds[typ];
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator it;
  int		i;

  if (typ == BST_GENERAL)
    {
      sm->general_pitch = pit;
      for (i = 0; i < BST_LAST_SOUND_TYPE; ++i)
	for (it = sm->sounds[i].begin(); it != sm->sounds[i].end(); ++it)
	  bunny_sound_pitch
	    (it->first,
	     it->second.proper_pitch
	     * sm->general_pitch
	     * sm->pitches[i]
	     );
    }
  else
    {
      sm->pitches[typ] = pit;
      for (it = map.begin(); it != map.end(); ++it)
	bunny_sound_pitch
	  (it->first,
	   it->second.proper_pitch
	   * sm->general_pitch
	   * sm->pitches[typ]
	   );
    }
}

