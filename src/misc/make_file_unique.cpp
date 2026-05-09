// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_make_file_unique
 * @doc-kind function
 * @doc-module misc
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Detaches loaded file data from the resource manager by duplicating it.
 * @param file File name used when the data was loaded.
 * @param data Data to duplicate.
 * @param len Size of data in bytes.
 * @return-success Returns a newly allocated copy of data.
 * @return-failure Returns NULL if the duplication fails.
 * @see bunny_load_file, bunny_delete_file
 *
 * @doc-lang fr
 * @brief Détache des données de fichier chargées du gestionnaire de ressources en les dupliquant.
 * @param file Nom du fichier utilisé lors du chargement.
 * @param data Données à dupliquer.
 * @param len Taille de data en octets.
 * @return-success Renvoie une nouvelle copie allouée de data.
 * @return-failure Renvoie NULL si la duplication échoue.
 * @see bunny_load_file, bunny_delete_file
 */
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

