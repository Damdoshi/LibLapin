// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*bunny_configuration_get_root(t_bunny_configuration	*conf)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_configuration_get_parent(conf)) == NULL)
    return (conf);
  return (bunny_configuration_get_root(cnf));
}

