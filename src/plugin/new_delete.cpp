// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%s library file -> %p"

/**
 * @doc
 * @doc-symbol bunny_new_plugin
 * @doc-kind function
 * @doc-module plugin
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Loads a bunny plugin dynamic library.
 * @description bunny_new_plugin opens the sent dynamic library, retrieves its mandatory __get_function_list function, validates the returned prototype list and stores the callable functions in a t_bunny_plugin object.
 * @param libfile The path of a dynamic library file respecting the bunny plugin format.
 * @return-case success On $Bsuccess@, returns a valid t_bunny_plugin pointer.
 * @return-case failure On $Bfailure@, returns NULL.
 * @error EINVAL The dynamic library cannot be opened, __get_function_list cannot be found, or __get_function_list returns NULL.
 * @error ENOMEM Out of memory.
 * @error BE_CONFIGURED_FUNCTION_NOT_FOUND A function listed by the plugin interface cannot be found in the loaded dynamic library.
 * @error BE_TOO_MANY_PARAMETERS A listed function describes more parameters than t_bunny_prototype can store.
 * @log "ressource,plugin"
 * @see t_bunny_plugin
 * @see t_bunny_get_function_list
 * @see bunny_delete_plugin
 * @see bunny_plugin_get_function
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 *
 * @doc-lang fr
 * @brief Charge une bibliothèque dynamique de plugin bunny.
 * @description bunny_new_plugin ouvre la bibliothèque dynamique envoyée, récupère sa fonction obligatoire __get_function_list, valide la liste de prototypes renvoyée et stocke les fonctions appelables dans un objet t_bunny_plugin.
 * @param libfile Le chemin d'un fichier de bibliothèque dynamique respectant le format de plugin bunny.
 * @return-case success En cas de $Bsuccès@, renvoie un pointeur t_bunny_plugin valide.
 * @return-case failure En cas d'$Béchec@, renvoie NULL.
 * @error EINVAL La bibliothèque dynamique ne peut pas être ouverte, __get_function_list est introuvable ou __get_function_list renvoie NULL.
 * @error ENOMEM Mémoire insuffisante.
 * @error BE_CONFIGURED_FUNCTION_NOT_FOUND Une fonction listée par l'interface de plugin est introuvable dans la bibliothèque dynamique chargée.
 * @error BE_TOO_MANY_PARAMETERS Une fonction listée décrit plus de paramètres que t_bunny_prototype ne peut en stocker.
 * @log "ressource,plugin"
 * @see t_bunny_plugin
 * @see t_bunny_get_function_list
 * @see bunny_delete_plugin
 * @see bunny_plugin_get_function
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 */
t_bunny_plugin		*bunny_new_plugin(const char			*libfile)
{
  const char		*last_param = "";
  t_bunny_buttplug	*plug;
  t_bunny_get_function_list func;
  const t_bunny_prototype *list;
  void			*handler;
  size_t		nbrfunc;
  int			err;

  // Load lib and get function list
#if			_WIN32 || __WIN32__
  if ((handler = LoadLibrary(libfile)) == NULL)
#else
  if ((handler = dlopen(libfile, RTLD_NOW)) == NULL)
#endif
    scream_error_if(return (NULL), EINVAL, PATTERN, "ressource,plugin", libfile, handler);

#if			_WIN32 || __WIN32__
  if ((func = (t_bunny_get_function_list)GetProcAddress((HMODULE)handler, "__get_function_list")) == NULL)
#else
  if ((func = (t_bunny_get_function_list)dlsym(handler, "__get_function_list")) == NULL)
#endif
    {
      bunny_errno = EINVAL;
      goto closelib;
    }
  if ((list = func()) == NULL)
    {
      bunny_errno = EINVAL;
      goto closelib;
    }

  // Allocate space for function array
  for (nbrfunc = 0; list[nbrfunc].function_ptr != NULL; ++nbrfunc);
  if ((plug = (t_bunny_buttplug*)bunny_malloc(sizeof(*plug) + nbrfunc * sizeof(plug->prototypes[0]))) == NULL)
    goto closelib;

  // Init structure
  if ((plug->name = bunny_strdup(libfile)) == NULL)
    goto freeplug;
  plug->library_handler = handler;
  plug->nbr_function = nbrfunc;

  // Load all functions
  for (nbrfunc = 0; list[nbrfunc].function_ptr != NULL; ++nbrfunc)
    {
      t_bunny_prototype	*proto = &plug->prototypes[nbrfunc];

#if			_WIN32 || __WIN32__
      if ((proto->function_ptr = (void*)GetProcAddress((HMODULE)handler, list[nbrfunc].name)) == NULL)
#else
      if ((proto->function_ptr = dlsym(handler, list[nbrfunc].name)) == NULL)
#endif
        {
          bunny_errno = BE_CONFIGURED_FUNCTION_NOT_FOUND;
	  goto freename;
        }
      if ((proto->nbr_parameters = list[nbrfunc].nbr_parameters) > NBRCELL(proto->parameters))
        {
          bunny_errno = BE_TOO_MANY_PARAMETERS;
	  goto unsupported_format;
        }
      proto->name = list[nbrfunc].name;
      proto->return_value = list[nbrfunc].return_value;
      memcpy(&proto->parameters[0], &list[nbrfunc].parameters[0], sizeof(proto->parameters));
    }

  scream_log_if(PATTERN, "ressource,plugin", libfile, plug);
  return ((t_bunny_plugin*)plug);

 unsupported_format:
  last_param = list[nbrfunc].name;
 freename:
  free(plug->name);
 freeplug:
  err = bunny_errno;
  bunny_free(plug);
  bunny_errno = err;
 closelib:
#if			_WIN32 || __WIN32__
  FreeLibrary((HMODULE)handler);
#else
  dlclose(handler);
#endif
  if (last_param)
    scream_error_if(return (NULL), bunny_errno, PATTERN " (Function %s have an unsupported format)", "ressource,plugin", libfile, (void*)NULL, last_param);
  else
    scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,plugin", libfile, (void*)NULL);
  return (NULL);
}

/**
 * @doc
 * @doc-symbol bunny_delete_plugin
 * @doc-kind function
 * @doc-module plugin
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Unloads and deletes a bunny plugin.
 * @description bunny_delete_plugin closes the dynamic library associated with plugin and releases the t_bunny_plugin object.
 * @param plugin The plugin to delete.
 * @log "ressource,plugin"
 * @see t_bunny_plugin
 * @see bunny_new_plugin
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 * @see bunny_plugin_get_function
 *
 * @doc-lang fr
 * @brief Décharge et détruit un plugin bunny.
 * @description bunny_delete_plugin ferme la bibliothèque dynamique associée à plugin et libère l'objet t_bunny_plugin.
 * @param plugin Le plugin à détruire.
 * @log "ressource,plugin"
 * @see t_bunny_plugin
 * @see bunny_new_plugin
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 * @see bunny_plugin_get_function
 */
void			bunny_delete_plugin(t_bunny_plugin	*plugin)
{
  free((void*)plugin->name);
#if			_WIN32 || __WIN32__
  FreeLibrary((HMODULE)plugin->library_handler);
#else
  dlclose((void*)plugin->library_handler);
#endif
  bunny_free(plugin);
  scream_log_if("%p", "ressource,plugin", plugin);
}


