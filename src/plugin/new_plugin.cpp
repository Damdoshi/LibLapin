// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include			<string.h>
#include			<dlfcn.h>
#include			"lapin_private.h"
#define				___STRZ(a)				#a

t_bunny_plugin			*bunny_new_plugin(const char		*dyn_lib)
{
  t_bunny_list_plugin_function	flist;
  void				*handler;
  const t_bunny_extern_function	*plug;
  size_t			len;
  struct bunny_plugin		*newplug;

  if ((handler = dlopen(dyn_lib, RTLD_NOW)) == NULL)
    return (NULL);
  if ((flist = (t_bunny_list_plugin_function)dlsym(handler, ___STRZ(BUNNY_GET_FUNC_LIST_FUNCTION))) == NULL)
    len = 0;
  else if ((plug = flist(&len)) == NULL)
    goto kill_lib;
  if ((newplug = (struct bunny_plugin*)bunny_malloc
       (sizeof(newplug->handler) +
	sizeof(newplug->nbr_functions) +
	len * sizeof(*plug))) == NULL)
    goto kill_lib;

  newplug->handler = handler;
  newplug->nbr_functions = len;
  memcpy(&newplug->functions[0], plug, len * sizeof(*plug));
  return ((t_bunny_plugin*)newplug);

 kill_lib:
  dlclose(handler);
  return (NULL);
}

