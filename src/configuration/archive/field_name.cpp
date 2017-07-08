// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_field_name(const t_bunny_ini_scope	*scope,
					      const t_bunny_ini_field	*field)
{
  const char		*str;

  (void)scope;
  str = bunny_configuration_get_name((t_bunny_configuration*)field);
  scream_log_if("%p scope, %p field -> %s", scope, field, str);
  return (str);
}

