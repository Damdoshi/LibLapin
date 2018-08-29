// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			SmallConf::Remove(const std::string	&str)
{
  delete nodes[str];
}

void			SmallConf::Remove(size_t		i)
{
  delete array[i];
}
