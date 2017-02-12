// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

const char		*bunny_configuration_get_name(const t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;

  return (conf->name.c_str());
}

