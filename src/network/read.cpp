// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		bunny_network_read(t_bunny_communication	*com)
{
  if (!com)
    return (false);
  return (gl_network.GetMessage(*(network::Communication*)com));
}

