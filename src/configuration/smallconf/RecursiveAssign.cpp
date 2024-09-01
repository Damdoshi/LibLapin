// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

bool			SmallConf::RecursiveAssign(SmallConf		&a,
						   const SmallConf	&b,
						   bool			hash,
						   bool			array)
{
  std::map<std::string, SmallConf*>::const_iterator it;
  size_t		i;

  a.NoComputeAssign(b);
  if (hash)
    {
      std::set<std::string> names;

      for (it = a.nodes.begin(); it != a.nodes.end(); ++it)
	if (it->second->name[0] != '.')
	  names.insert(it->second->name);
      for (auto itx = names.begin(); itx != names.end(); ++itx)
	a.nodes.erase(*itx);
      for (it = b.Begin(); it != b.End(); ++it)
	if (it->first[0] != '.')
	  if (RecursiveAssign(a[it->first], b[it->first], hash, array) == false)
	    return (false);
    }
  if (array)
    {
      while (a.array.size())
	a.Remove(a.array.size() - 1);
      for (i = 0; i < b.Size(); ++i)
	if (b[i].name[0] != '.')
	  if (RecursiveAssign(a[i], b[i], hash, array) == false)
	    return (false);
    }
  return (true);
}
