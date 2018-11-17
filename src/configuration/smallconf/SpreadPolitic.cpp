// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			SmallConf::SpreadPolitic(void)
{
  std::map<std::string, SmallConf*>::iterator n;
  std::vector<SmallConf*>::iterator a;

  if (father != NULL)
    {
      if (father->is_const == RECURSIVE_POLITIC)
	is_const = DYNAMIC_POLITIC;
      if (father->is_solid == RECURSIVE_POLITIC)
	is_solid = DYNAMIC_POLITIC;
      if (father->is_eternal == RECURSIVE_POLITIC)
	is_eternal = DYNAMIC_POLITIC;
      if (is_eternal != NO_POLITIC)
	father->is_eternal = DYNAMIC_POLITIC;
    }

  for (n = nodes.begin(); n != nodes.end(); ++n)
    n->second->SpreadPolitic();

  for (a = array.begin(); a != array.end(); ++a)
    (*a)->SpreadPolitic();

  if (is_eternal != NO_POLITIC)
    father->is_eternal = DYNAMIC_POLITIC;
}

