// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_sound_manager_stop_sound
 * @doc-module sound_manager
 * @doc-kind function
 * @doc-order 280
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stops a registered sound effect through a manager.
 * @param sm Sound manager containing the effect.
 * @param snd Effect to stop.
 * @see bunny_sound_manager_play_sound
 *
 * @doc-lang fr
 * @brief Arrête un effet sonore enregistré via un gestionnaire.
 * @param sm Gestionnaire de sons contenant l'effet.
 * @param snd Effet à arrêter.
 * @see bunny_sound_manager_play_sound
 */
void		bunny_sound_manager_stop_sound(t_bunny_sound_manager	*_sm,
					       t_bunny_effect		*_snd)
{
  struct bunny_sound_manager *sm = (struct bunny_sound_manager*)_sm;
  std::map<t_bunny_sound*, t_bunny_managed_sound>::iterator it;
  std::map<t_bunny_sound*, t_bunny_sound_type>::iterator itx;
  t_bunny_sound	*snd = (t_bunny_sound*)_snd;

  if ((itx = sm->sound_to_type.find(snd)) == sm->sound_to_type.end())
    return ;
  if ((it = sm->sounds[itx->second].find(snd)) == sm->sounds[itx->second].end())
    return ;
  bunny_sound_stop(it->first);
}

