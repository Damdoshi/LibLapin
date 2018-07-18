/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_RESSOURCE_MANAGER_HPP__
# define			__LAPIN_PRIVATE_RESSOURCE_MANAGER_HPP__
# include			<unordered_map>
# include			<array>
# include			<list>
# include			"fluidsynth.h"

class				ResManager
{
public:
  typedef void			(*t_delete_ressource)(void	*res);
  enum				Type
  {
    SF_RENDERTEXTURE,
    SF_TEXTURE,
    SF_IMAGE,
    SF_FONT,
    SF_SOUNDBUFFER,
    BUNNY_PIXELS,
    BUNNY_PICTURE,
    BUNNY_SAMPLE,
    LOADED_FILE,
    SIZE_LOADED_FILE,
    FLUID_FONT,
    FLUID_PLAYER,
    LAST_TYPE
  };
  static const std::string	TypeName[LAST_TYPE];
  bool				disable_manager;

  struct			Ressource
  {
    void			*real_ressource;
    std::set<void*>		user_side_ressource;
  };

  // Key is the hash of the ressource file or any id
  std::array<
    std::unordered_map<
      uint64_t, Ressource
      >, LAST_TYPE>		 ressources;

  void				*AddToPool(Type			typ,
					   const char		*file,
					   uint64_t		id,
					   void			*t_bunny_thing,
					   void			*sf_thing)
  {
    Ressource			*res = NULL;

    try
      {
	res = &ressources[typ][id];
	if (!res->real_ressource)
	  {
	    res->real_ressource = sf_thing;
	    scream_log_if("%s %s:%lu - *Real* loading", "manager", TypeName[typ].c_str(), file, id);
	  }
	else
	  scream_log_if("%s %s:%lu - Shallow loading", "manager", TypeName[typ].c_str(), file, id);
	res->user_side_ressource.insert(t_bunny_thing);
      }
    catch (...)
      {
	if (res && res->user_side_ressource.empty())
	  ressources[typ].erase(id);
	return (NULL);
      }
    return (sf_thing);
  }

  void				*TryGet(Type			typ,
					uint64_t		id)
  {
    std::unordered_map<uint64_t, Ressource>::iterator		it;

    if ((it = ressources[typ].find(id)) == ressources[typ].end())
      return (NULL);
    return (it->second.real_ressource);
  }

  bool				IsAlone(Type			typ,
					uint64_t		id,
					void			*t_bunny_thing) const
  {
    std::unordered_map<uint64_t, Ressource>::const_iterator	it;

    if ((it = ressources[typ].find(id)) == ressources[typ].end())
      return (false);
    if (it->second.user_side_ressource.size() != 1)
      return (false);
    if (it->second.user_side_ressource.find(t_bunny_thing) == it->second.user_side_ressource.end())
      return (false);
    return (true);
  }

  size_t			NbrLoad(Type			typ,
					uint64_t		id) const
  {
    std::unordered_map<uint64_t, Ressource>::const_iterator	it;

    if ((it = ressources[typ].find(id)) == ressources[typ].end())
      return (0);
    return (it->second.user_side_ressource.size());
  }

  bool				Extract(Type			typ,
					uint64_t		id,
					void			*t_bunny_thing)
  {
    std::unordered_map<uint64_t, Ressource>::iterator		it;

    if ((it = ressources[typ].find(id)) == ressources[typ].end())
      return (false);
    if (it->second.user_side_ressource.erase(t_bunny_thing) == 0)
      return (false);
    // Do not erase the real ressource, it is unique now.
    if (it->second.user_side_ressource.empty())
      ressources[typ].erase(id);
    return (true);
  }

  bool				TryRemove(Type			typ,
					  uint64_t		id,
					  void			*t_bunny_thing)
  {
    std::unordered_map<uint64_t, Ressource>::iterator		it;

    if ((it = ressources[typ].find(id)) == ressources[typ].end())
      return (false);
    if (it->second.user_side_ressource.erase(t_bunny_thing) == 0)
      return (false);
    if (it->second.user_side_ressource.empty())
      {
	if (typ == SF_RENDERTEXTURE)
	  delete (sf::RenderTexture*)it->second.real_ressource;
	else if (typ == SF_TEXTURE)
	  delete (sf::Texture*)it->second.real_ressource;
	else if (typ == SF_IMAGE)
	  delete (sf::Image*)it->second.real_ressource;
	else if (typ == SF_FONT)
	  delete (sf::Font*)it->second.real_ressource;
	else if (typ == SF_SOUNDBUFFER)
	  delete (sf::SoundBuffer*)it->second.real_ressource;
	else if (typ == BUNNY_PIXELS)
	  bunny_free(it->second.real_ressource);
	else if (typ == BUNNY_PICTURE)
	  bunny_delete_clipable((t_bunny_clipable*)it->second.real_ressource);
	else if (typ == BUNNY_SAMPLE)
	  bunny_free(it->second.real_ressource);
	else if (typ == LOADED_FILE)
	  bunny_free(it->second.real_ressource);
	else if (typ == SIZE_LOADED_FILE)
	  {}
	else if (typ == FLUID_FONT)
	  fluid_synth_sfunload(gl_fluid_synth, (int)(size_t)it->second.real_ressource, 0);
	else if (typ == FLUID_PLAYER)
	  delete_fluid_player((fluid_player_t*)it->second.real_ressource);
	ressources[typ].erase(id);
      }
    return(true);
  }

  ResManager(void)
  {}

  ~ResManager(void)
  {
    std::array<std::unordered_map<uint64_t, Ressource>, LAST_TYPE>::iterator itx;
    std::unordered_map<uint64_t, Ressource>::iterator		it;
    int								i;

    for (itx = ressources.begin(), i = 0; itx != ressources.end(); ++itx, ++i)
      {
	for (it = itx->begin(); it != itx->end(); ++it)
	  {
	    if (i == SF_RENDERTEXTURE)
	      delete (sf::RenderTexture*)it->second.real_ressource;
	  }
	// Could remove also bunny types, but that would prevent
	// the technocore to trace leaks when notating pupils
	itx->clear();
      }
  }
};

extern ResManager		RessourceManager;

#endif	//			__LAPIN_PRIVATE_RESSOURCE_MANAGER_HPP__
