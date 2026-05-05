// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_sound_manager_play_sound
 * @doc-module sound_manager
 * @doc-kind function
 * @doc-order 260
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Plays a registered sound effect through a manager.
 * @param sm Sound manager containing the effect.
 * @param snd Effect to play.
 * @return-success true if the effect was found and played.
 * @return-failure false if the effect is not registered.
 * @see bunny_sound_manager_stop_sound, bunny_sound_manager_add
 *
 * @doc-lang fr
 * @brief Joue un effet sonore enregistré via un gestionnaire.
 * @param sm Gestionnaire de sons contenant l'effet.
 * @param snd Effet à jouer.
 * @return-success true si l'effet a été trouvé et joué.
 * @return-failure false si l'effet n'est pas enregistré.
 * @see bunny_sound_manager_stop_sound, bunny_sound_manager_add
 */
bool		bunny_sound_manager_play_sound(t_bunny_sound_manager	*_sm,
					       t_bunny_effect		*_snd)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator it;
  std::map<t_bunny_sound*, t_bunny_sound_type>::iterator itx;
  t_bunny_sound	*snd = (t_bunny_sound*)_snd;

  if ((itx = sm->sound_to_type.find(snd)) == sm->sound_to_type.end())
    return (false);
  if ((it = sm->sounds[itx->second].find(snd)) == sm->sounds[itx->second].end())
    return (false);
  bunny_sound_play(it->first);
  return (true);
}
