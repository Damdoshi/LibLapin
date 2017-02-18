// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_configuration_set_string(t_bunny_configuration	*config,
						       const char		*val)
{
  SmallConf		*conf = (SmallConf*)config;

  if (val == NULL)
    conf->SetString(std::string());
  else
    conf->SetString(std::string(val));
}

void			bunny_configuration_set_int(t_bunny_configuration	*config,
						    int				val)
{
  SmallConf		*conf = (SmallConf*)config;

  conf->SetInt(val);
}

void			bunny_configuration_set_double(t_bunny_configuration	*config,
						       double			val)
{
  SmallConf		*conf = (SmallConf*)config;

  conf->SetDouble(val);
}

