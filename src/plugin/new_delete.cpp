// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			<dlfcn.h>
#include			"lapin_private.h"

#define				PATTERN		"%s library file -> %p"

t_bunny_plugin			*bunny_new_plugin(const char			*libfile)
{
  const char			*last_param = "";
  t_bunny_buttplug		*plug;
  t_bunny_get_function_list	func;
  const t_bunny_prototype	*list;
  void				*handler;
  size_t			nbrfunc;
  int				err;

  // Load lib and get function list
  if ((handler = dlopen(libfile, RTLD_NOW)) == NULL)
    scream_error_if(return (NULL), EINVAL, PATTERN, "ressource,plugin", libfile, handler);

  if ((func = (t_bunny_get_function_list)dlsym(handler, "__get_function_list")) == NULL)
    {
      bunny_errno = EINVAL;
      goto closelib;
    }
  list = func();

  // Allocate space for function array
  for (nbrfunc = 0; list[nbrfunc].function_ptr != NULL; ++nbrfunc);
  if ((plug = (t_bunny_buttplug*)bunny_malloc(sizeof(*plug) + nbrfunc * sizeof(plug->prototypes[0]))) == NULL)
    goto closelib;

  // Init structure
  if ((plug->name = strdup(libfile)) == NULL)
    goto freeplug;
  plug->library_handler = handler;
  plug->nbr_function = nbrfunc;

  // Load all functions
  for (nbrfunc = 0; list[nbrfunc].function_ptr != NULL; ++nbrfunc)
    {
      t_bunny_prototype		*proto = &plug->prototypes[nbrfunc];

      if ((proto->function_ptr = dlsym(handler, list[nbrfunc].name)) == NULL)
	goto freename;
      if ((proto->nbrparam = list[nbrfunc].nbrparam) > 4)
	goto unsupported_format;
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
  dlclose(handler);
  if (last_param)
    scream_error_if(return (NULL), bunny_errno, PATTERN " (Function %s have an unsupported format)", "ressource,plugin", libfile, (void*)NULL, last_param);
  else
    scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,plugin", libfile, (void*)NULL);
  return (NULL);
}

void				bunny_delete_plugin(t_bunny_plugin	*plugin)
{
  free((void*)plugin->name);
  dlclose((void*)plugin->library_handler);
  bunny_free(plugin);
  scream_log_if("%p", "ressource,plugin", plugin);
}


