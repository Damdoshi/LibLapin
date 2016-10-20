// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include			"lapin_private.h"
#define				___STRZ(a)				#a

t_bunny_plugin			*bunny_new_plugin(const char		*dyn_lib)
{
  t_bunny_list_plugin_function	flist;
  void				*handler;
  const t_bunny_plugin		*plug;
  size_t			len;
  t_bunny_plugin		*newplug;

  if ((handler = dlopen(dyn_lib, RTLD_NOW)) == NULL)
    return (NULL);
  if ((flist = dlsym(handler, ___STRZ(BUNNY_GET_FUNC_LIST_FUNCTION))) == NULL)
    len = 0;
  else if ((plug = flist(&len)) == NULL)
    goto kill_lib;
  if ((newplug = bunny_malloc
       (sizeof(newplug->handler) +
	sizeof(newplug->nbr_functions) +
	len * sizeof(*plug))) == NULL)
    goto kill_lib;

  newplug->handler = handler;
  newplug->nbr_functions = len;
  memcpy(&newplug->functions[0], plug, len * sizeof(*plug));
  return (newplug);

 kill_lib:
  dlclose(handler);
  return (NULL);
}

