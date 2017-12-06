// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%p ini, %s scope, %s field, %u index -> %s"

const char		*bunny_ini_get_field(const t_bunny_ini		*ini,
					     const char			*scope,
					     const char			*field,
					     unsigned int		index)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)ini;
  const char		*c = NULL;

  if (strcmp(scope, "") != 0)
    {
      if ((cnf = bunny_configuration_get_child(cnf, scope)) == NULL)
	scream_error_if
	  (return (NULL), bunny_errno, PATTERN, "cofiguration", ini, scope, field, index, c);
    }
  if ((cnf = bunny_configuration_get_child(cnf, field)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "configuration", ini, scope, field, index, c);
  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "configuration", ini, scope, field, index, c);
  if (bunny_configuration_get_string(cnf, &c) == false)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "configuration", ini, scope, field, index, c);
  scream_log_if(PATTERN, "configuration", ini, scope, field, index, c);
  return (c);
}

