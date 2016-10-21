// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		<string.h>
#include		"lapin_private.h"

bool			bunny_call(t_bunny_plugin	*plugin,
				   const char		*func,
				   const char		*paramdesc,
				   t_bunny_value	*out,
				   t_bunny_value	*params)
{
  size_t		i;

  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->functions[i].name, func) == 0)
      {
	if (strcmp(plugin->functions[i].parameters, paramdesc) != 0)
	  return (false);
	if (out != NULL)
	  *out = plugin->functions[i].fptr(strlen(paramdesc), params);
	else
	  plugin->functions[i].fptr(strlen(paramdesc), params);
	return (true);
      }
  return (true);
}

bool			bunny_vcall(t_bunny_plugin	*plugin,
				    const char		*func,
				    const char		*paramdesc,
				    t_bunny_value	*out,
				    ...)
{
  va_list		lst;
  t_bunny_value		*param;
  int			i, len;
  
  param = (t_bunny_value*)alloca((len = strlen(func)) * sizeof(*param));
  va_start(lst, out);
  for (i = 0; i < len; ++i)
    param[i] = va_arg(lst, t_bunny_value);
  va_end(lst);
  return (bunny_call(plugin, func, paramdesc, out, param));
}

