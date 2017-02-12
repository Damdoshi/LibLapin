// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<sstream>
#include		"lapin_private.h"

t_bunny_configuration	*bunny_configuration_get_case(t_bunny_configuration	*conf,
						      size_t			n)
{
  SmallConf		*c = (SmallConf*)conf;

  try
    {
      return ((t_bunny_configuration*)&(*c)[n]);
    }
  catch (...)
    {}
  return (NULL);
}

