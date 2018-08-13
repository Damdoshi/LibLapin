// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	"steam_api.h"
#include	"lapin_private.h"

bool		gl_bunny_init_steam = false;

bool		bunny_connect_to_steam(t_bunny_steam		*st)
{
  struct bunny_steam *steam = (struct bunny_steam*)st;

  if (gl_bunny_init_steam == false)
    {
      if (steam->game_id != 0 && SteamAPI_RestartAppIfNecessary(steam->game_id))
	return (false);
      if ((gl_bunny_init_steam = SteamAPI_Init()) == false)
	return (false);
    }
  steam->game_id = game_id;
  steam->username = SteamFriends()->GetPersonaName();
  gl_steam_callback = SteamAPI_RunCallbacks;
  return (true);
}
