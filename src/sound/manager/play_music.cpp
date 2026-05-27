// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_sound_manager_play_music
 * @doc-module sound_manager
 * @doc-kind function
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Plays a registered music on a manager track.
 * @param sm Sound manager containing the music.
 * @param snd Music to play.
 * @param n Track on which the music must be played; BST_ALL restarts from BST_TRACK_01 after stopping every track.
 * @return-success true if the music is now playing or was already playing.
 * @return-failure false if the music is not registered.
 * @see bunny_sound_manager_stop_music, bunny_sound_manager_add
 *
 * @doc-lang fr
 * @brief Joue une musique enregistrée sur une piste du gestionnaire.
 * @param sm Gestionnaire de sons contenant la musique.
 * @param snd Musique à jouer.
 * @param n Piste sur laquelle la musique doit être jouée ; BST_ALL redémarre sur BST_TRACK_01 après avoir arrêté toutes les pistes.
 * @return-success true si la musique joue maintenant ou jouait déjà.
 * @return-failure false si la musique n'est pas enregistrée.
 * @see bunny_sound_manager_stop_music, bunny_sound_manager_add
 */
bool		bunny_sound_manager_play_music(t_bunny_sound_manager	*_sm,
					       t_bunny_music		*_snd,
					       t_bunny_music_track	n)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  t_bunny_sound	*snd = (t_bunny_sound*)_snd;
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator it;

  if ((it = sm->sounds[BST_MUSIC].find(snd)) == sm->sounds[BST_MUSIC].end())
    return (false);
  if (n == BST_ALL)
    {
      bunny_sound_manager_stop_music(_sm, n);
      n = BST_TRACK_01;
    }
  else if (sm->current_music[n] != NULL)
    {
      if (sm->current_music[n] == snd)
	return (true);
      bunny_sound_stop(sm->current_music[n]);
    }
  sm->current_music[n] = it->first;
  bunny_sound_play(it->first);
  return (true);
}
