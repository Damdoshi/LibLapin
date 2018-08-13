// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	"steam_api.h"
#include	"lapin_private.h"

extern bool	gl_bunny_init_steam;

void		bunny_close_steam(t_bunny_steam		*steam)
{
  if (gl_bunny_init_system)
    SteamAPI_Shutdown();
  if (steam)
    bunny_free(steam);
}
