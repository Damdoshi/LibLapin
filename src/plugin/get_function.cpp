// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p plugin, %s function name -> %p"

void			*bunny_plugin_get_function(const t_bunny_plugin	*plugin,
						   const char		*name)
{
  void			*ret;

#if			_WIN32 || __WIN32__
  if ((ret = ((void*)GetProcAddress((HMODULE)plugin->library_handler, name))) == NULL)
#else
  if ((ret = (dlsym((void*)plugin->library_handler, name))) == NULL)
#endif
    scream_error_if(return (NULL), EINVAL, PATTERN, "plugin", plugin, name, (void*)NULL);
  scream_log_if(PATTERN, "plugin", plugin, name, ret);
  return (ret);
}

