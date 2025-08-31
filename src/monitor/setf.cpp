// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin Library

#include		"lapin_private.h"

bool			bunny_configuration_vgetf_node(t_bunny_configuration    *cnf,
						       t_bunny_configuration	**data,
						       const char               *pat,
						       va_list                  lst);

bool			_bunny_monitor_setf(t_bunny_monitored_type		type,
					    void				*data,
					    const char				*pattern,
					    ...)
{
  bool			cmode = bunny_configuration_get_create_mode();
  t_bunny_configuration	*layer = gl_monitor_conf[gl_monitor_top];
  SmallConf		*node;
  va_list		lst;
  bool			ret;

  if (layer == NULL)
    {
      if (gl_monitor_top >= NBRCELL(gl_monitor_conf))
	return (false);
      if ((gl_monitor_conf[gl_monitor_top] = layer = bunny_new_configuration()) == NULL)
	return (false);
    }

  va_start(lst, pattern);
  if (data != NULL)
    bunny_configuration_create_mode(true);
  if (!bunny_configuration_vgetf_node(layer, (t_bunny_configuration**)&node, pattern, lst))
    goto Exit;

  if (data == NULL)
    {
      bunny_delete_configuration(node);
      return (true);
    }

  // On prend des valeurs distantes et non pas des copies.
  if (type == BMT_STRING)
    node->distant_string = (char**)data;
  else if (type == BMT_INTEGER)
    node->distant_int = (int*)data;
  else if (type == BMT_DOUBLE)
    node->distant_double = (double*)data;
  else
    goto Exit;
  bunny_configuration_create_mode(cmode);
  return (true);

 Exit:
  bunny_configuration_create_mode(cmode);
  return (false);
}
