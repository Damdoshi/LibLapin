// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_ini_scope	*bunny_ini_get_scope(t_bunny_ini		*ini,
					     const char			*scope)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)ini;

  if (strcmp(scope, "") == 0)
    scope = "@";
  if ((cnf = bunny_configuration_get_child(cnf, scope)) == NULL)
    return (NULL);
  return ((t_bunny_ini_scope*)cnf);
}

