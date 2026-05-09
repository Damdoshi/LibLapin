// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<fcntl.h>
#include		<unistd.h>
#include		"lapin_private.h"

#define			PATTERN		"%s file, %p target for data, %p target for data size -> %zd"


/**
 * @doc
 * @doc-symbol bunny_load_file
 * @doc-kind function
 * @doc-module misc
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Loads a complete file into memory.
 * @description The loaded data is managed by LibLapin's resource manager unless resource management is disabled. If size is NULL, the allocated buffer receives an additional final zero byte.
 * @param file File path to load.
 * @param data Where to store the loaded data pointer.
 * @param size Where to store the loaded size, or NULL to request a zero-terminated buffer.
 * @return-success Returns the loaded byte count.
 * @return-failure Returns -1 on error and leaves data and size unchanged.
 * @log "ressource,file"
 * @see bunny_save_file, bunny_make_file_unique, bunny_delete_file
 *
 * @doc-lang fr
 * @brief Charge un fichier complet en mémoire.
 * @description Les données chargées sont gérées par le gestionnaire de ressources de la LibLapin sauf si celui-ci est désactivé. Si size vaut NULL, le tampon alloué reçoit un octet zéro final supplémentaire.
 * @param file Chemin du fichier à charger.
 * @param data Adresse où stocker le pointeur vers les données chargées.
 * @param size Adresse où stocker la taille chargée, ou NULL pour demander un tampon terminé par zéro.
 * @return-success Renvoie le nombre d'octets chargés.
 * @return-failure Renvoie -1 en cas d'erreur et ne modifie pas data ni size.
 * @log "ressource,file"
 * @see bunny_save_file, bunny_make_file_unique, bunny_delete_file
 */
ssize_t			bunny_load_file(const char		*file,
					void			**data,
					size_t			*size)
{
  uint64_t		hash;
  char			*buf;
  int			fd;
  int			sk, sz;

  hash = bunny_hash(BH_FNV, file, strlen(file));
  if (RessourceManager.disable_manager == false &&
      (buf = (char*)RessourceManager.TryGet(ResManager::LOADED_FILE, hash)) != NULL)
    sk = (size_t)RessourceManager.TryGet(ResManager::SIZE_LOADED_FILE, hash);
  else
    {
      if ((fd = open(file, O_RDONLY | O_BINARY)) == -1)
	scream_error_if
	  (return (-1), bunny_errno, PATTERN, "ressource,file", file, data, size, (ssize_t)-1);
      if ((sk = lseek(fd, 0, SEEK_END)) == -1)
	goto close_and_quit;
      lseek(fd, 0, SEEK_SET);
      sz = sk + 1;
      if ((buf = (char*)bunny_malloc(sz * sizeof(*buf))) == NULL)
	goto close_and_quit;
      if ((sz = read(fd, buf, sk)) != sk)
	{
	  bunny_free(buf);
	  goto close_and_quit;
	}
      close(fd);
      buf[sz] = '\0';
    }

  if (size)
    *size = sk;
  *data = buf;
  if (RessourceManager.disable_manager == false)
    {
      RessourceManager.AddToPool
	(ResManager::LOADED_FILE, file,
	 hash,
	 (void*)RessourceManager.NbrLoad(ResManager::LOADED_FILE, hash),
	 *data);
      RessourceManager.AddToPool
	(ResManager::SIZE_LOADED_FILE, file,
	 hash,
	 (void*)RessourceManager.NbrLoad(ResManager::SIZE_LOADED_FILE, hash),
	 (void*)(size_t)sk);
    }
  scream_log_if(PATTERN, "ressource,file", file, data, size, (ssize_t)sk);
  return (sk);

 close_and_quit:
  close(fd);
  scream_error_if(return (-1), bunny_errno, PATTERN, "ressource,file", file, data, size, (ssize_t)-1);
  return (-1);
}

