// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_sound_manager_stop_music
 * @doc-module sound_manager
 * @doc-kind function
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stops the music playing on a manager track.
 * @param sm Sound manager to edit.
 * @param n Track to stop, or BST_ALL for every track.
 * @see bunny_sound_manager_play_music
 *
 * @doc-lang fr
 * @brief Arrête la musique jouée sur une piste du gestionnaire.
 * @param sm Gestionnaire de sons à modifier.
 * @param n Piste à arrêter, ou BST_ALL pour toutes les pistes.
 * @see bunny_sound_manager_play_music
 */
void		bunny_sound_manager_stop_music(t_bunny_sound_manager	*_sm,
					       t_bunny_music_track	n)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  int		i;

  if (n < -1 || n >= BST_LAST_TRACK)
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
