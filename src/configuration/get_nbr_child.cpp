// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sstream>
#include		"lapin_private.h"

size_t			bunny_configuration_get_nbr_child(const t_bunny_configuration	*_conf)
{
  SmallConf		*conf = (SmallConf*)_conf;

  scream_log_if("%p -> %zu", "configuration", conf, conf->Size());
  return (conf->NbrChild());
}


