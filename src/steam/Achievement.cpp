// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		BunnySteam::SetAchievement(const std::string	&name)
{
  if (!user)
    return (false);
  if (user->SetAchievement(name.c_str()) == false)
    return (false);
  achievements[name] = true;
  return (true);
}

bool		BunnySteam::GetAchievement(const std::string	&name) const
{
  std::map<std::string, bool>::const_iterator it = achievements.find(name);

  return (it != achievements.end() ? *it : false);
}

