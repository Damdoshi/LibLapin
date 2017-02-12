// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*bunny_configuration_get_child(t_bunny_configuration	*conf,
						       const char		*child)
{
  SmallConf		*c = (SmallConf*)conf;
  std::string		str = child;

  try
    {
      return ((t_bunny_configuration*)&(*c)[str]);
    }
  catch (...)
    {}
  return (NULL);
}

