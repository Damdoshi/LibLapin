/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_RESSOURCE_MANAGER_HPP__
# define			__LAPIN_PRIVATE_RESSOURCE_MANAGER_HPP__
# include			<list>

class				ResManager
{
public:
  typedef void			(*t_delete_ressource)(void	*res);

  struct			Ressource
  {
    t_delete_ressource		delete_func;
    void			*real_ressource;
    std::set<void*>		user_side_ressource;
  };

  // Key is the hash of the ressource file or any id
  std::unordered_map<uint32_t, Ressource> ressources;

  void				AddToPool(uint32_t		id,
					  t_delete_ressource	delete_func,
					  void			*t_bunny_thing
					  void			*sf_thing)
  {
    Ressource			*res = NULL;

    try
      {
	res = &ressources[id];
	res->real_ressource = sf_thing;
	res->user_side_ressource.insert(t_bunny_thing);
      }
    catch (...)
      {
	if (res && res->user_side_ressource.empty())
	  ressources.erase(id);
	return (NULL);
      }
    res->delete_func = delete_func;
    return (sf_thing);
  }

  bool				TryRemove(uint32_t		id,
					  void			*t_bunny_thing)
  {
    std::unordered_map<uint32_t, Ressource>::iterator		it;

    if ((it = ressources.find(id)) == ressources.end())
      return (false);
    if (it->second.user_side_ressource.erase(t_bunny_thing) == 0)
      return (false);
    if (it->second.user_side_ressource.empty())
      {
	it->second.delete_func(it->second.real_ressource);
	ressources.erase(id);
      }
    return(true);
  }

  ResManager(void)
  {}

  ~ResManager(void)
  {
    std::unordered_map<uint32_t, Ressource>::iterator		it;

    for (it = ressources.begin(); it != ressources.end(); ++it)
      it->second.delete_func(it->second.real_ressources);
    ressources.clear();
  }
};

extern hbs::ResManager		RessourceManager;

#endif	//			__LAPIN_PRIVATE_RESSOURCE_MANAGER_HPP__
