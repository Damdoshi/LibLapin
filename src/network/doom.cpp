// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_doom(const t_bunny_network	*a)
{
  if (!a)
    return (false);
  return (gl_network.Doom(*(network::Info*)a));
}

