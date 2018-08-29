// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

bool			SmallConf::RecursiveCheck(const SmallConf	&a,
						  const SmallConf	&b)
{
  std::map<std::string, SmallConf*>::const_iterator it;
  size_t		i;

  if (a != b)
    return (false);
  for (it = a.Begin(); it != a.End(); ++it)
    if (b.Access(it->first) == false)
      return (false);
    else if (SmallConf::RecursiveCheck(*it->second, b[it->first]) == false)
      return (false);
  for (i = 0; i < a.Size(); ++i)
    if (b.Access(i) == false)
      return (false);
    else if (SmallConf::RecursiveCheck(a[i], b[i]) == false)
      return (false);
  return (true);
}

