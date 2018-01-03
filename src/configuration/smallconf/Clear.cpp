// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			SmallConf::Clear(void)
{
  std::map<std::string, SmallConf*>::iterator	it;
  std::map<std::string, SmallConf*> dup = nodes;
  std::vector<SmallConf*> dupx = array;
  std::vector<SmallConf*>::iterator itx;

  if (sequence)
    {
      delete sequence;
      sequence = NULL;
    }
  if (expression)
    {
      delete expression;
      expression = NULL;
    }
  if (function)
    {
      delete function;
      function = NULL;
    }

  for (it = dup.begin(); it != dup.end(); ++it)
    {
      it->second->father = NULL;
      delete it->second;
    }
  nodes.clear();

  for (itx = dupx.begin(); itx != dupx.end(); ++itx)
    delete *itx;
  dupx.clear();

  if (father != NULL)
    {
      if (father->nodes.find(name) != father->nodes.end())
	father->nodes.erase(name);
      for (itx = father->array.begin(); itx != father->array.end(); ++itx)
	if (*itx == this)
	  {
	    father->array.erase(itx);
	    return ;
	  }
    }
}

