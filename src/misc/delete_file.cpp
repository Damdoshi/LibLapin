// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_delete_file(void		*data,
					  const char	*file)
{
  uint64_t		hash;

  if (file)
    hash = bunny_hash(BH_FNV, file, strlen(file));
  if (!file || RessourceManager.NbrLoad(ResManager::LOADED_FILE, hash) == 0)
    {
      bunny_free(data);
      return ;
    }
  RessourceManager.TryRemove
    (ResManager::LOADED_FILE, hash,
     (void*)(RessourceManager.NbrLoad(ResManager::LOADED_FILE, hash) - 1));
  RessourceManager.TryRemove
    (ResManager::SIZE_LOADED_FILE, hash,
     (void*)(RessourceManager.NbrLoad(ResManager::SIZE_LOADED_FILE, hash) - 1));
}

