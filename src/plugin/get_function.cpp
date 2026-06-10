// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p plugin, %s function name -> %p"

/**
 * @doc
 * @doc-symbol bunny_plugin_get_function
 * @doc-kind function
 * @doc-module plugin
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Retrieves a symbol from a loaded plugin.
 * @description bunny_plugin_get_function returns a function pointer from the dynamic library represented by plugin. The requested symbol does not need to be listed in the bunny plugin interface.
 * @param plugin The loaded dynamic library in which funcname is searched.
 * @param funcname The name of the function or symbol to fetch.
 * @return-case success On $Bsuccess@, returns the address of the requested symbol. You must cast it to the correct type yourself.
 * @return-case failure On $Bfailure@, returns NULL.
 * @error EINVAL funcname cannot be found inside plugin.
 * @log "plugin"
 * @see t_bunny_plugin
 * @see bunny_new_plugin
 * @see bunny_delete_plugin
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 *
 * @doc-lang fr
 * @brief Récupère un symbole depuis un plugin chargé.
 * @description bunny_plugin_get_function renvoie un pointeur de fonction depuis la bibliothèque dynamique représentée par plugin. Le symbole demandé n'a pas besoin d'être listé dans l'interface de plugin bunny.
 * @param plugin La bibliothèque dynamique chargée dans laquelle funcname est recherché.
 * @param funcname Le nom de la fonction ou du symbole à récupérer.
 * @return-case success En cas de $Bsuccès@, renvoie l'adresse du symbole demandé. Vous devez le convertir vous-même vers le bon type.
 * @return-case failure En cas d'$Béchec@, renvoie NULL.
 * @error EINVAL funcname est introuvable dans plugin.
 * @log "plugin"
 * @see t_bunny_plugin
 * @see bunny_new_plugin
 * @see bunny_delete_plugin
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 */
void			*bunny_plugin_get_function(const t_bunny_plugin	*plugin,
						   const char		*name)
{
  void			*ret;

#if			_WIN32 || __WIN32__
  if ((ret = ((void*)GetProcAddress((HMODULE)plugin->library_handler, name))) == NULL)
#else
  if ((ret = (dlsym((void*)plugin->library_handler, name))) == NULL)
#endif
    scream_error_if(return (NULL), EINVAL, PATTERN, "plugin", plugin, name, (void*)NULL);
  scream_log_if(PATTERN, "plugin", plugin, name, ret);
  return (ret);
}

