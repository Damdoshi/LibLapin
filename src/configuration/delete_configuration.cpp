// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_delete_configuration(t_bunny_configuration	*conf)
{
  SmallConf		*c = (SmallConf*)conf;

  scream_log_if("%p", "ressource,configuration", c);
  delete c;
}

