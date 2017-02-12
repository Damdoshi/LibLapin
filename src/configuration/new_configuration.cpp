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
      return (NULL);
    }
  return ((t_bunny_configuration*)conf);
}

