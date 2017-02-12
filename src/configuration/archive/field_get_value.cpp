// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_field_get_value(const t_bunny_ini_field	*field,
						   unsigned int			index)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)field;
  const char		*c;

  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    return (NULL);
  if (bunny_configuration_get_string(cnf, &c) == false)
    return (NULL);
  return (c);
}

