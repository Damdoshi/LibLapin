// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_delete_node(t_bunny_configuration		*conf,
					  const char			*str)
{
  SmallConf		*c = (SmallConf*)bunny_configuration_go_get_node(conf, str);

  if (!c)
    return ;
  scream_log_if("%p", "ressource,configuration", c);
  delete c;
}

