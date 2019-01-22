// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

extern bool	gl_bunny_init_steam;

void		bunny_close_steam(t_bunny_steam		*steam)
{
  if (gl_bunny_init_steam)
    {
      SteamAPI_Shutdown();
      gl_bunny_init_steam = false;
    }
  if (steam)
    delete steam;
}
