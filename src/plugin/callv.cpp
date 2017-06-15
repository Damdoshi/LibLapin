// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_plugin_callv(t_bunny_plugin		*plugin,
					   const char			*func,
					   t_bunny_value		*return_value,
					   ...)
{
  va_list		lst;
  t_bunny_value		val
    [sizeof(plugin->prototypes[0].parameters) / sizeof(t_bunny_value_type)];
  size_t		i, j;
  size_t		len;

  va_start(lst, return_value);
  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->prototypes[i].name, func) == 0)
      {
	for (j = 0, len = plugin->prototypes[i].nbrparam; j < len; ++j)
	  memcpy(&val[i], va_arg(lst, t_bunny_value*), sizeof(val[i]));
	va_end(lst);
	_real_call(&plugin->prototypes[i], return_value, len, &val[0]);
	return (true);
      }
  va_end(lst);
  return (false);
}

