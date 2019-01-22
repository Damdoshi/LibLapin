// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	<limits.h>
#include	"lapin_private.h"

bool		BunnySteam::SetStatistic(const std::string	&name,
					 int			value)
{
  if (!user)
    return (false);
  if (stats->SetStat(name.c_str(), value) == false)
    return (false);
  statistics[name] = value;
  return (true);
}

int		BunnySteam::GetStatistic(const std::string	&name) const
{
  std::map<std::string, int>::const_iterator it = statistics.find(name);

  return (it != statistics.end() ? it->second : INT_MIN);
}

