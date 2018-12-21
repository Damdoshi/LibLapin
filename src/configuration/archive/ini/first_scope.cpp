// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_scope	*bunny_ini_first_scope(t_bunny_ini		*in)
{
  t_bunny_ini_scope	*ini;

  ini = bunny_configuration_first((t_bunny_configuration*)in);
  while (ini && bunny_configuration_get_nbr_child(ini) == 0)
    ini = bunny_configuration_next((t_bunny_configuration*)ini);
  scream_log_if("%p -> %p", "configuration", in, ini);
  return (ini);
}

