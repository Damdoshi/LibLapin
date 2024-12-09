// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

int		bunny_network_inbox(void)
{
  return (gl_network.GetReceivedPacketCount());
}

