// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*bunny_configuration_get_parent(t_bunny_configuration	*conf)
{
  SmallConf		*c = (SmallConf*)conf;
  t_bunny_configuration	*cnf = (t_bunny_configuration*)c->father;

  scream_log_if("%p -> %p", "configuration", conf, cnf);
  return (cnf);
}

