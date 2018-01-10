// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		bunny_sound_manager_stop_music(t_bunny_sound_manager	*_sm,
					       t_bunny_music_track	n)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  int		i;

  if (sm->current_music == NULL || n < -1 || n >= BST_LAST_TRACK)
    return ;
  if (n == BST_ALL)
    for (i = 0; i < BST_LAST_TRACK; ++i)
      {
	bunny_sound_stop(sm->current_music[i]);
	sm->current_music[i] = NULL;
      }
  else
    {
      bunny_sound_stop(sm->current_music[n]);
      sm->current_music[n] = NULL;
    }
}
