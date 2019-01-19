// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

bool		bunny_steam_set_achievement(t_bunny_steam	*steam,
					    const char		*id)
{
  struct bunny_steam *st = (struct bunny_steam*)steam;

  if (st->stats_were_received == false)
    return (false);
  SteamUserStats()->SetAchievement(id);
  return (SteamUserStats()->StoreStats());
}

