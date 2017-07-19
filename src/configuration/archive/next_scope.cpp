// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_scope	*bunny_ini_next_scope(t_bunny_ini		*in,
					      t_bunny_ini_scope		*scope)
{
  t_bunny_ini_scope	*ini;

  (void)in;
  ini = (t_bunny_ini_scope*)bunny_configuration_next((t_bunny_configuration*)scope);
  while (ini && bunny_configuration_get_nbr_child(ini) == 0)
    ini = bunny_configuration_next((t_bunny_configuration*)ini);
  scream_log_if("%p ini, %p scope -> %p", in, scope, ini);
  return (ini);
}

