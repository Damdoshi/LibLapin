// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			SmallConf::create_mode = false;

t_bunny_configuration	*bunny_new_configuration(void)
{
  SmallConf		*conf;

  try
    {
      conf = new SmallConf;
    }
  catch (...)
    {
      scream_error_if(return (NULL), ENOMEM, " -> %p", "ressource,configuration", (void*)NULL);
    }
  scream_log_if(" -> %p", "ressource,configuration", conf);
  return ((t_bunny_configuration*)conf);
}

