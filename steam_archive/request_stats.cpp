// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

bool		bunny_steam_request_stats(void)
{
  if (SteamUserStats() == NULL
      || SteamUser() == NULL
      || SteamUser()->BLoggedOn() == false
      )
    return (false);
  return (SteamUserStats()->RequestCurrentStats());
}

