// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

bool			SmallConf::Access(const std::string		&str) const
{
  return (nodes.find(str) != nodes.end());
}

bool			SmallConf::Access(ssize_t			i) const
{
  return (i >= 0 && i < (ssize_t)array.size());
}

