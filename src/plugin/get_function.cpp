// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			*bunny_plugin_get_function(t_bunny_plugin	*plugin,
						   const char		*str)
{
  return (dlsym(plugin->handler, str));
}

