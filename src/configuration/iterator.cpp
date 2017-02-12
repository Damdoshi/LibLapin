// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*bunny_configuration_first(t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;

  if (conf->Begin() == conf->End())
    return (NULL);
  return ((t_bunny_configuration*)conf->Begin()->second);
}

t_bunny_configuration	*bunny_configuration_next(t_bunny_configuration		*config)
{
  SmallConf		*conf = (SmallConf*)config;

  ++conf->father->It();
  if (conf->father->It() == conf->father->End())
    return (NULL);
  return ((t_bunny_configuration*)conf->father->It()->second);
}

t_bunny_configuration	*bunny_configuration_end(t_bunny_configuration		*config)
{
  (void)config;
  return (NULL);
}

