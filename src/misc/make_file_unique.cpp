// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			*bunny_make_file_unique(const char	*file,
						const void	*data,
						size_t		len)
{
  uint64_t		hash;

  hash = bunny_hash(BH_FNV, file, strlen(file));
  RessourceManager.Extract
    (ResManager::LOADED_FILE, hash,
     (void*)(RessourceManager.NbrLoad(ResManager::LOADED_FILE, hash) - 1));
  RessourceManager.Extract
    (ResManager::SIZE_LOADED_FILE, hash,
     (void*)(RessourceManager.NbrLoad(ResManager::LOADED_FILE, hash) - 1));
  return (bunny_memdup(data, len + 1));
}

