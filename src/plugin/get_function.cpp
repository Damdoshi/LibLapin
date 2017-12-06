// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<dlfcn.h>
#include		"lapin_private.h"

#define			PATTERN "%p plugin, %s function name -> %p"

void			*bunny_plugin_get_function(const t_bunny_plugin	*plugin,
						   const char		*name)
{
  void			*ret;

  if ((ret = (dlsym((void*)plugin->library_handler, name))) == NULL)
    scream_error_if(return (NULL), EINVAL, PATTERN, "plugin", plugin, name, (void*)NULL);
  scream_log_if(PATTERN, "plugin", plugin, name, ret);
  return (ret);
}

