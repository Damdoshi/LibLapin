// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_scope_get_field(const t_bunny_ini_scope	*sc,
						   const char			*field,
						   unsigned int			index)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)sc;
  const char		*c;

  if ((cnf = bunny_configuration_get_child(cnf, field)) == NULL)
    return (NULL);
  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    return (NULL);
  if (bunny_configuration_get_string(cnf, &c) == false)
    return (NULL);
  return (c);
}

