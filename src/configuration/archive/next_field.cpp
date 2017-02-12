// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_field	*bunny_ini_next_field(t_bunny_ini_scope		*scope,
					      t_bunny_ini_field		*field)
{
  (void)scope;
  return ((t_bunny_ini_field*)bunny_configuration_next((t_bunny_configuration*)field));
}

