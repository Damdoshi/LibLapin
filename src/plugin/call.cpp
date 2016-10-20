// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		<string.h>
#include		"lapin_private.h"

bool			bunny_call(t_bunny_plugin	*plugin,
				   const char		*func,
				   const char		*paramdesc,
				   t_bunny_value_type	*out,
				   t_bunny_value_type	*params)
{
  size_t		i;

  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->functions[i].name, func) == 0)
      {
	if (strcmp(plugin->functions[i].parameters, paramdesc) != 0)
	  return (false);
	if (out != NULL)
	  *out = plugin->functions[i].fptr(strlen(param), params);
	else
	  plugin->functions[i].fptr(strlen(param), params);
	return (true);
      }
  return (true);
}

bool			bunny_vcall(t_bunny_plugin	*plugin,
				    const char		*func,
				    const char		*paramdesc,
				    t_bunny_value_type	*out,
				    ...)
{
  va_list		lst;
  t_bunny_value_type	*param;
  int			i, len;
  
  param = alloca((len = strlen(func)) * sizeof(*param));
  va_start(lst, out);
  for (i = 0; i < len; ++i)
    param[i] = &va_arg(lst, t_bunny_value_type);
  va_end(lst);
  return (bunny_call(plugin, func, paramdesc, out, param));
}

