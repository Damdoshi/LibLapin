// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<dlfcn.h>
#include		"lapin_private.h"

void			*bunny_plugin_get_function(const t_bunny_plugin	*plugin,
						   const char		*name)
{
  return (dlsym((void*)plugin->library_handler, name));
}

