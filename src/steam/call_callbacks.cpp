// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

void		bunny_steam_call_callbacks(void)
{
  if (gl_steam_callback)
    gl_steam_callback();
}

