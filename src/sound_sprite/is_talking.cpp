// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_sound_sprite_is_talking(t_bunny_sound_sprite	*spr)
{
  if (spr->last_played_slice == NULL)
    return (false);
  double	cur = bunny_sound_get_cursor(&spr->soundset.sound);

  return (cur - spr->last_played_slice->index <=
	  spr->last_played_slice->active_duration
	  * spr->last_played_slice->sound.pitch);
}

