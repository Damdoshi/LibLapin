// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p -> %p"

t_bunny_configuration	*bunny_configuration_first(t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;
  t_bunny_configuration	*cnf;

  if (conf->Begin() == conf->End())
    {
      scream_log_if(PATTERN, "configuration", config, (void*)NULL);
      return (NULL);
    }
  cnf = (t_bunny_configuration*)conf->Begin()->second;
  scream_log_if(PATTERN, "configuration", config, cnf);
  return (cnf);
}

t_bunny_configuration	*bunny_configuration_next(t_bunny_configuration		*config)
{
  SmallConf		*conf = (SmallConf*)config;
  t_bunny_configuration	*cnf;

  ++conf->father->It();
  if (conf->father->It() == conf->father->End())
    {
      scream_log_if(PATTERN, "configuration", config, (void*)NULL);
      return (NULL);
    }
  cnf = (t_bunny_configuration*)conf->father->It()->second;
  scream_log_if(PATTERN, "configuration", config, cnf);
  return (cnf);
}

t_bunny_configuration	*bunny_configuration_end(t_bunny_configuration		*config)
{
  (void)config;
  scream_log_if(PATTERN, "configuration", config, (void*)NULL);
  return (NULL);
}

