// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%s library file -> %p"

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


