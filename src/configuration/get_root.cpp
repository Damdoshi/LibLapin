// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p -> %p"

t_bunny_configuration	*bunny_configuration_get_root(t_bunny_configuration	*conf)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_configuration_get_parent(conf)) == NULL)
    {
      scream_log_if(PATTERN, "configuration", conf, conf);
      return (conf);
    }
  cnf = bunny_configuration_get_root(cnf);
  scream_log_if(PATTERN, "configuration", conf, cnf);
  return (cnf);
}

