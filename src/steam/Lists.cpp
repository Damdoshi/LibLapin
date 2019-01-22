// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char * const	*BunnySteam::AchievementList(void) const
{
  static const char	*buf[1024];
  std::map<std::string, bool>::const_iterator it;
  size_t		i;

  for (it = achievements.begin(), i = 0; it != achievements.end(); ++it, ++i)
    buf[i] = it->first.c_str();
  buf[i] = NULL;
  return (&buf[0]);
}

const char * const	*BunnySteam::StatisticList(void) const
{
  static const char	*buf[1024];
  std::map<std::string, int>::const_iterator it;
  size_t		i;

  for (it = statistics.begin(), i = 0; it != statistics.end(); ++it, ++i)
    buf[i] = it->first.c_str();
  buf[i] = NULL;
  return (&buf[0]);
}

