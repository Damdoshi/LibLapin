// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_delete_file
 * @doc-kind function
 * @doc-module misc
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Releases data returned by bunny_load_file.
 * @param data Loaded data to release.
 * @param file File name used during loading, or NULL for unmanaged data.
 * @description Managed data is released through the resource manager. Unmanaged data is released with bunny_free.
 * @see bunny_load_file, bunny_make_file_unique
 *
 * @doc-lang fr
 * @brief Libère des données renvoyées par bunny_load_file.
 * @param data Données chargées à libérer.
 * @param file Nom du fichier utilisé lors du chargement, ou NULL pour des données non gérées.
 * @description Les données gérées passent par le gestionnaire de ressources. Les données non gérées sont libérées avec bunny_free.
 * @see bunny_load_file, bunny_make_file_unique
 */
void			bunny_delete_file(void		*data,
					  const char	*file)
{
  uint64_t		hash;

  if (file)
    hash = bunny_hash(BH_FNV, file, strlen(file));
  if (RessourceManager.disable_manager ||
      !file || RessourceManager.NbrLoad(ResManager::LOADED_FILE, hash) == 0)
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

