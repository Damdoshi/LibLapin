// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_doom(t_bunny_network_info		a)
{
  return (gl_network.Doom(*(network::Info*)&a));
}

