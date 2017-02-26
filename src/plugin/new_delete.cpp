// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			<dlfcn.h>
#include			"lapin_private.h"

t_bunny_plugin			*bunny_new_plugin(const char			*libfile)
{
  t_bunny_buttplug		*plug;
  t_bunny_get_function_list	func;
  const t_bunny_prototype	*list;
  void				*handler;
  size_t			nbrfunc;
 
  if ((handler = dlopen(libfile, RTLD_NOW)) == NULL)
    return (NULL);
  if ((func = (t_bunny_get_function_list)dlsym(handler, "__get_function_list")) == NULL)
    goto closelib;
  list = func();

  for (nbrfunc = 0; list[nbrfunc].function_ptr != NULL; ++nbrfunc);
  if ((plug = (t_bunny_buttplug*)bunny_malloc(sizeof(*plug) + nbrfunc * sizeof(plug->prototypes[0]))) == NULL)
    goto closelib;
  if ((plug->name = strdup(libfile)) == NULL)
    goto freeplug;
  plug->library_handler = handler;
  plug->nbr_function = nbrfunc;
  for (nbrfunc = 0; list[nbrfunc].function_ptr != NULL; ++nbrfunc)
    {
      t_bunny_prototype		*proto = &plug->prototypes[nbrfunc];

      if ((proto->function_ptr = dlsym(handler, list[nbrfunc].name)) == NULL)
	goto freename;
      if ((proto->nbrparam = list[nbrfunc].nbrparam) > 4)
	goto freename;
      proto->name = list[nbrfunc].name;
      proto->return_value = list[nbrfunc].return_value;
      memcpy(&proto->parameters[0], &list[nbrfunc].parameters[0], sizeof(proto->parameters));
    }

  return ((t_bunny_plugin*)plug);

 freename:
  free(plug->name);
 freeplug:
  bunny_free(plug);
 closelib:
  dlclose(handler);
  return (NULL);
}

void				bunny_delete_plugin(t_bunny_plugin	*plugin)
{
  free((void*)plugin->name);
  dlclose((void*)plugin->library_handler);
  bunny_free(plugin);
}


