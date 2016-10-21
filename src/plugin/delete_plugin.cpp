// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		<dlfcn.h>
#include		"lapin_private.h"

void			bunny_delete_plugin(t_bunny_plugin	*plugin)
{
  dlclose(plugin->handler);
  // Do not delete strings inside the plugin => they are litterals from the plugin
  bunny_free(plugin);
}

