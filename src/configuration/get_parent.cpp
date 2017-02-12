// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*bunny_configuration_get_parent(t_bunny_configuration	*conf)
{
  SmallConf		*c = (SmallConf*)conf;

  return ((t_bunny_configuration*)c->father);
}

