// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

const char		*bunny_ini_get_field(const t_bunny_ini		*ini,
					     const char			*scope,
					     const char			*field,
					     unsigned int		index)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)ini;
  const char		*c;

  if (strcmp(scope, "") == 0)
    scope = "@";
  if ((cnf = bunny_configuration_get_child(cnf, scope)) == NULL)
    return (NULL);
  if ((cnf = bunny_configuration_get_child(cnf, field)) == NULL)
    return (NULL);
  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    return (NULL);
  if (bunny_configuration_get_string(cnf, &c) == false)
    return (NULL);
  return (c);
}

