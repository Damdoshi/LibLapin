// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		bunny_sound_manager_volume(t_bunny_sound_manager	*_sm,
					   t_bunny_sound_type		typ,
					   double			vol)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_managed_sound> &map = sm->sounds[typ];
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator it;
  double	final;
  int		i;

  if (typ == BST_GENERAL)
    {
      sm->general_volume = vol;
      for (i = 0; i < BST_LAST_SOUND_TYPE; ++i)
	for (it = sm->sounds[i].begin(); it != sm->sounds[i].end(); ++it)
	  {
	    final =
	      (it->second.proper_volume / 100.0)
	      * (sm->general_volume / 100.0)
	      * (sm->volumes[i] / 100.0)
	      * 100.0;
	    bunny_sound_volume(it->first, final);
	  }
    }
  else
    {
      sm->volumes[typ] = vol;
      for (it = map.begin(); it != map.end(); ++it)
	{
	  final =
	    (it->second.proper_volume / 100.0)
	    * (sm->general_volume / 100.0)
	    * (sm->volumes[typ] / 100.0)
	    * 100.0;
	  bunny_sound_volume(it->first, final);
	}
    }
}

