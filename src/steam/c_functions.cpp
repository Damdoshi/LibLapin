// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_steam		*bunny_connect_to_steam(uint64_t		game_id)
{
  BunnySteam		*steam;

  if ((steam = new (std::nothrow) BunnySteam) == NULL)
    return (NULL);
  if (steam->Start(game_id) != GO_ON)
    return (NULL);
  return ((t_bunny_steam*)steam);
}

void			bunny_close_steam(t_bunny_steam			*s)
{
  BunnySteam		*steam = (BunnySteam*)s;

  s->Stop();
  delete steam;
}

t_bunny_response	bunny_handle_events(t_bunny_steam		*s,
					    void			*data)
{
  BunnySteam		*steam = (BunnySteam*)s;

  return (steam->HandleEvents(data));
}

void			bunny_set_achievement(t_bunny_steam		*steam,
					      const char		*name)
{
  ((BunnySteam*)steam)->SetAchievement(name);
}

bool			bunny_get_achievement(t_bunny_steam		*steam,
					      const char		*name)
{
  return (((BunnySteam*)steam)->GetAchievement(name));
}

const char * const	*bunny_get_achievement_list(t_bunny_steam	*steam)
{
  return (((BunnySteam*)steam)->AchievementList());
}

void			bunny_set_statistic(t_bunny_steam		*steam,
					    const char			*name,
					    int				val)
{
  ((BunnySteam*)steam)->SetStatistic(name, val);
}

int			bunny_get_statistic(t_bunny_steam		*steam,
					    const char			*name)
{
  return (((BunnySteam*)steam)->GetStatistic(name));
}

const char * const	*bunny_get_statistic_list(t_bunny_steam		*steam)
{
  return (((BunnySteam*)steam)->StatisticList());
}

