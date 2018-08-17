// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

bool		gl_bunny_init_steam = false;

t_bunny_steam	*bunny_connect_to_steam(uint64_t			game_id,
					t_bunny_steam_configuration	*st)
{
  struct bunny_steam *steam;

  if (st == NULL)
    return (NULL);
  if (gl_bunny_init_steam == false)
    {
      if (game_id != 0 && SteamAPI_RestartAppIfNecessary(game_id))
	return (NULL);
      if ((gl_bunny_init_steam = SteamAPI_Init()) == false)
	return (NULL);
    }
  steam = new struct bunny_steam;
  steam->game_id = game_id;
  steam->username = SteamFriends()->GetPersonaName();
  steam->configuration = st;
  steam->last_error = NULL;
  steam->stats_were_received = false;
  steam->user = SteamUser();
  steam->stats = SteamUserStats();
  gl_steam_callback = SteamAPI_RunCallbacks;
  return ((t_bunny_steam*)steam);
}
