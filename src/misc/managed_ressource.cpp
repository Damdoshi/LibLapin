// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
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

void			bunny_managed_ressource(void)
{
  size_t		j = 0;
  size_t		i = 0;

  std::cout << "MANAGED RESSOURCE LIST:" << std::endl;
  for (auto &&mp : RessourceManager.ressources)
    {
      if (mp.size())
	std::cout << "TYPE :" << ResManager::TypeName[j] << std::endl;
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

void			bunny_set_ressource_management(bool		enabled)
{
  RessourceManager.disable_manager = !enabled;
}

