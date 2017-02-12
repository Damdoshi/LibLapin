// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_scope	*bunny_ini_first_scope(t_bunny_ini		*in)
{
  return (bunny_configuration_first((t_bunny_configuration*)in));
}

