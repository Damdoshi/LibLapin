// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_configuration_get_string(const t_bunny_configuration *config,
						       const char		**str)
{
  SmallConf		*conf = (SmallConf*)config;

  return (conf->GetString(str));
}

bool			bunny_configuration_get_double(const t_bunny_configuration *config,
						       double			*val)
{
  SmallConf		*conf = (SmallConf*)config;

  return (conf->GetDouble(val));
}

bool			bunny_configuration_get_int(const t_bunny_configuration	*config,
						    int				*val)
{
  SmallConf		*conf = (SmallConf*)config;

  return (conf->GetInt(val));
}

