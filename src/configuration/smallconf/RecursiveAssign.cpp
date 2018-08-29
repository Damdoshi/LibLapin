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

  a = b;
  if (hash)
    for (it = b.Begin(); it != b.End(); ++it)
      if (RecursiveAssign(a[it->first], b[it->first], hash, array) == false)
	return (false);
  if (array)
    for (i = 0; i < b.Size(); ++i)
      if (RecursiveAssign(a[i], b[i], hash, array) == false)
	return (false);
  return (true);
}

