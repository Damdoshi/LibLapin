// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p field, %u index -> %s"

const char		*bunny_ini_field_get_value(const t_bunny_ini_field	*field,
						   unsigned int			index)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)field;
  const char		*c = NULL;

  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    {
      scream_log_if(PATTERN, "configuration", field, index, c);
      return (NULL);
    }
  if (bunny_configuration_get_string(cnf, &c) == false)
    {
      scream_log_if(PATTERN, "configuration", field, index, c);
      return (NULL);
    }
  scream_log_if(PATTERN, "configuration", field, index, c);
  return (c);
}

