// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<sstream>
#include		"lapin_private.h"

size_t			bunny_configuration_get_nbr_case(const t_bunny_configuration	*conf)
{
  size_t		i;

  for (i = 0; bunny_configuration_get_case((t_bunny_configuration*)conf, i); ++i);
  return (i);
}

