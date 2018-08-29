// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p ini, %s scope -> %p"

t_bunny_ini_scope	*bunny_ini_get_scope(t_bunny_ini		*ini,
					     const char			*scope)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)ini;

  if (strcmp(scope, "") == 0)
    return (ini);
  if ((cnf = bunny_configuration_get_child(cnf, scope)) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "configuration", ini, scope, cnf);
  if (bunny_configuration_get_nbr_child(cnf) == 0)
    scream_error_if
      (return (NULL), BE_CANNOT_FIND_ELEMENT, PATTERN, "configuration", ini, scope, cnf);
  scream_log_if(PATTERN, "configuration", ini, scope, cnf);
  return ((t_bunny_ini_scope*)cnf);
}

