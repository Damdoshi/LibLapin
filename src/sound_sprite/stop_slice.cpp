// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_sound_sprite_stop_slice(t_bunny_sound_sprite	*sprite)
{
  struct bunny_music *music = (struct bunny_music*)sprite;

  if (sprite->last_played_slice == NULL)
    return (false);
  if (music->sound_manager)
    bunny_sound_manager_stop_music((t_bunny_sound_manager*)music->sound_manager, sprite->track);
  else
    bunny_sound_stop(&sprite->soundset.sound);
  *((t_bunny_sound_slice**)&sprite->last_played_slice) = NULL;
  *(t_bunny_music_track*)&sprite->track = BST_LAST_TRACK;
  return (true);
}

