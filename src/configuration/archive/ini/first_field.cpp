// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_field	*bunny_ini_first_field(t_bunny_ini_scope	*scope)
{
  t_bunny_ini_field	*ini;

  ini = bunny_configuration_first((t_bunny_configuration*)scope);
  scream_log_if("%p -> %p", "configuration", scope, ini);
  return (ini);
}

