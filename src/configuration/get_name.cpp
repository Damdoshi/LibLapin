// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p -> %s"

const char		*bunny_configuration_get_name(const t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;

  if (conf->name == "@")
    {
      scream_log_if(PATTERN, "configuration", config, "");
      return ("");
    }
  scream_log_if(PATTERN, "configuration", config, conf->name.c_str());
  return (conf->name.c_str());
}

