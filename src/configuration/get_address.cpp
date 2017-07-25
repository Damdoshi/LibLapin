// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	"lapin_private.h"

#define		PATTERN		"%p -> %s"

const char	*bunny_configuration_get_address(const t_bunny_configuration *config)
{
  SmallConf	*conf = (SmallConf*)config;

  return (conf->address.c_str());
}

