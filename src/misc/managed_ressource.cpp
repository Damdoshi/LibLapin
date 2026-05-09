// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<iostream>
#include		"lapin_private.h"

const std::string	ResManager::TypeName[ResManager::LAST_TYPE] =
  {
    "sf::RenderTexture*",
    "Sf::Texture*",
    "Sf::Image*",
    "sf::Font*",
    "sf::SoundBuffer*",
    "void * const (pixels)",
    "t_bunny_picture* (For fontz)",
    "void * const (sample)",
    "void * (file)",
    "size_t (size of file)"
  };


/**
 * @doc
 * @doc-symbol bunny_managed_ressource
 * @doc-kind function
 * @doc-module misc
 * @doc-order 380
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Prints the resources currently tracked by the resource manager.
 * @description This is a diagnostic helper that writes a human-readable list to standard output.
 * @see bunny_set_ressource_management
 *
 * @doc-lang fr
 * @brief Affiche les ressources actuellement suivies par le gestionnaire de ressources.
 * @description C'est un utilitaire de diagnostic qui écrit une liste lisible sur la sortie standard.
 * @see bunny_set_ressource_management
 */
void			bunny_managed_ressource(void)
{
  size_t		j = 0;
  size_t		i = 0;

  std::cout << "MANAGED RESSOURCE LIST:" << std::endl;
  for (auto &&mp : RessourceManager.ressources)
    {
      if (mp.size())
	std::cout << "TYPE :" << ResManager::TypeName[j]
		  << " (" << mp.size() << ")" << std::endl;
      for (auto &&res : mp)
	{
	  std::cout << "ID " << res.first
		    << " Ressource " << res.second.real_ressource
		    << " is used by " << res.second.user_side_ressource.size()
		    << " wrappers."
		    << std::endl;
	  i += 1;
	}
      j += 1;
    }
  std::cout << "TOTAL: " << i << std::endl;
}


/**
 * @doc
 * @doc-symbol bunny_set_ressource_management
 * @doc-kind function
 * @doc-module misc
 * @doc-order 390
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enables or disables LibLapin resource sharing.
 * @param enabled true to enable resource management, false to disable it.
 * @description When disabled, repeated loads are not shared by the resource manager.
 * @see bunny_managed_ressource, bunny_load_file
 *
 * @doc-lang fr
 * @brief Active ou désactive le partage de ressources de la LibLapin.
 * @param enabled true pour activer la gestion des ressources, false pour la désactiver.
 * @description Lorsqu'elle est désactivée, les chargements répétés ne sont plus partagés par le gestionnaire de ressources.
 * @see bunny_managed_ressource, bunny_load_file
 */
void			bunny_set_ressource_management(bool		enabled)
{
  RessourceManager.disable_manager = !enabled;
}

