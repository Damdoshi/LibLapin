// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<sstream>
#include		"lapin_private.h"

size_t			bunny_configuration_get_nbr_child(const t_bunny_configuration	*_conf)
{
  t_bunny_configuration	*conf = (t_bunny_configuration*)_conf;
  t_bunny_configuration	*cnf;
  size_t		i;

  for (cnf = bunny_configuration_first(conf);
       cnf != bunny_configuration_end(conf);
       cnf = bunny_configuration_next(cnf))
    i += 1;
  return (i);
}

