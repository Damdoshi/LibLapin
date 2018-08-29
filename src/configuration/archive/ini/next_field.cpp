// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_field	*bunny_ini_next_field(t_bunny_ini_scope		*scope,
					      t_bunny_ini_field		*field)
{
  t_bunny_ini_field	*ini;

  (void)scope;
  ini = (t_bunny_ini_field*)bunny_configuration_next((t_bunny_configuration*)field);
  scream_log_if("%p scope, %p field -> %p", "configuration", scope, field, ini);
  return (ini);
}

