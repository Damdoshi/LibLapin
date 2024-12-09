// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_poll(double		tmout)
{
  return (gl_network.Poll(tmout, false));
}

