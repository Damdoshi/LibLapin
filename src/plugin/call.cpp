// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p plugin, %s function name, %p target for return value, %zu parameter array length, %p parameters -> %s"

bool			bunny_plugin_call(t_bunny_plugin		*plugin,
					  const char			*func,
					  t_bunny_value			*return_value,
					  size_t			arrlen,
					  t_bunny_value			*params)
{
  size_t		i;

  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->prototypes[i].name, func) == 0)
      {
	if (plugin->prototypes[i].nbrparam != arrlen)
	  scream_error_if(return (false), EINVAL, PATTERN " (Invalid array length)",
			  "plugin",
			  plugin, func, return_value, arrlen, params, "false");
	_real_call(&plugin->prototypes[i], return_value, arrlen, params);
	scream_log_if
	  (PATTERN, "plugin", plugin, func, return_value, arrlen, params, "true");
	return (true);
      }
  scream_error_if(return (false), EINVAL, PATTERN " (Cannot find function name)",
		  "plugin", plugin, func, return_value, arrlen, params, "false");
  return (false);
}
