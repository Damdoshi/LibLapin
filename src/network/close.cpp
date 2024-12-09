// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_close(const t_bunny_network_info		*inf)
{
  if (!inf)
    return (false);
  return (gl_network.Close(*(network::Info*)inf));
}

