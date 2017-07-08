// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<math.h>
#include		"lapin_private.h"

bool			bunny_configuration_get_string(const t_bunny_configuration *config,
						       const char		**str)
{
  SmallConf		*conf = (SmallConf*)config;
  bool			ret;

  ret = conf->GetString(str);
  scream_log_if
    ("%p conf, %p target  -> %s (%s)",
     config, str, ret ? "true" : "false", ret ? *str : "");
  return (ret);
}

bool			bunny_configuration_get_double(const t_bunny_configuration *config,
						       double			*val)
{
  SmallConf		*conf = (SmallConf*)config;
  bool			ret;

  ret = conf->GetDouble(val);
  scream_log_if
    ("%p conf, %p target  -> %s (%f)",
     config, val, ret ? "true" : "false", ret ? *val : nan(""));
  return (ret);
}

bool			bunny_configuration_get_int(const t_bunny_configuration	*config,
						    int				*val)
{
  SmallConf		*conf = (SmallConf*)config;
  bool			ret;

  ret = conf->GetInt(val);
  scream_log_if
    ("%p conf, %p target  -> %s (%d)",
     config, val, ret ? "true" : "false", ret ? *val : 0);
  return (ret);
}

