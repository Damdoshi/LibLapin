// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_configuration_is_last(t_bunny_configuration	*cnf)
{
  std::map<std::string, SmallConf*>::iterator it;
  SmallConf		*conf = (SmallConf*)cnf;

  it = conf->father->iterator;
  return (++it == conf->father->End());
}
