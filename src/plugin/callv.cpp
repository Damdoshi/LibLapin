// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p plugin, %s function name, %p target for return value -> %s"

bool			bunny_plugin_callv(t_bunny_plugin		*plugin,
					   const char			*func,
					   t_bunny_value		*return_value,
					   ...)
{
  va_list		lst;
  size_t		ptr;
  double		rel;
  t_bunny_value		val
    [sizeof(plugin->prototypes[0].parameters) / sizeof(t_bunny_value_type)];
  size_t		i, j;
  size_t		len;

  va_start(lst, return_value);
  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->prototypes[i].name, func) == 0)
      {
	for (j = 0, len = plugin->prototypes[i].nbrparam; j < len; ++j)
	  {
	    if (plugin->prototypes[i].parameters[j] == BVT_DOUBLE)
	      {
		rel = va_arg(lst, double);
		val[j].real = rel;
	      }
	    else
	      {
		ptr = va_arg(lst, size_t);
		memcpy(&val[j], &ptr, sizeof(val[j]));
	      }
	  }
	va_end(lst);
	_real_call(&plugin->prototypes[i], return_value, len, &val[0]);
	scream_log_if(PATTERN, "ressource,plugin", plugin, func, return_value, "true");
	return (true);
      }
  va_end(lst);
  scream_error_if(return (false), EINVAL, PATTERN " (Cannot find function name)",
		  "ressource,plugin", plugin, func, return_value, "false");
  return (false);
}

