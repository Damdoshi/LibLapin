// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			SmallConf::Remove(const std::string	&str)
{
  if (nodes[str])
    {
      nodes[str]->father = NULL;
      delete nodes[str];
    }
  nodes.erase(str);
}

void			SmallConf::Remove(size_t		i)
{
  if (array[i])
    {
      array[i]->father = NULL;
      delete array[i];
    }
  array.erase(array.begin() + i);
}
