// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p sc, %s field, %u index -> %s"

const char		*bunny_ini_scope_get_field(const t_bunny_ini_scope	*sc,
						   const char			*field,
						   unsigned int			index)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)sc;
  const char		*c = NULL;

  if ((cnf = bunny_configuration_get_child(cnf, field)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, sc, field, index, c);
  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, sc, field, index, c);
  if (bunny_configuration_get_string(cnf, &c) == false)
    scream_error_if(return (NULL), bunny_errno, PATTERN, sc, field, index, c);
  scream_log_if(PATTERN, sc, field, index, c);
  return (c);
}

