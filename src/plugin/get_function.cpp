// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			*bunny_plugin_get_function(const t_bunny_plugin	*plugin,
						   const char		*name)
{
  size_t		i;

  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(name, plugin->prototypes[i].name) == 0)
      return ((void*)plugin->prototypes[i].function_ptr);
  return (NULL);
}

