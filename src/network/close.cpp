// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_close(t_bunny_network_info		inf)
{
  return (gl_network.Close(*(network::Info*)&inf));
}

