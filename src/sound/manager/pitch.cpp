// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_sound_manager_pitch
 * @doc-module sound_manager
 * @doc-kind function
 * @doc-order 320
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets the global pitch or a category pitch in a manager.
 * @description Existing managed sounds in the affected scope are updated immediately.
 * @param sm Sound manager to modify.
 * @param typ BST_GENERAL for global pitch, or the category to modify.
 * @param pit Pitch to set.
 * @see bunny_sound_manager_volume, bunny_managed_sound_pitch
 *
 * @doc-lang fr
 * @brief Définit la hauteur globale ou la hauteur d'une catégorie dans un gestionnaire.
 * @description Les sons gérés déjà présents dans le périmètre concerné sont mis à jour immédiatement.
 * @param sm Gestionnaire de sons à modifier.
 * @param typ BST_GENERAL pour la hauteur globale, ou la catégorie à modifier.
 * @param pit Hauteur à fixer.
 * @see bunny_sound_manager_volume, bunny_managed_sound_pitch
 */
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

