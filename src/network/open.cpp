// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include			"lapin_private.h"

const t_bunny_network_info     *bunny_network_open(t_bunny_protocol	pcol,
						   size_t		size,
						   char			term,
						   uint16_t		port,
						   const char		*ip)
{
  if (!ip)
    ip = "";
  return ((const t_bunny_network_info*)gl_network.Open((Network::Protocol)pcol, size, term, port, ip));
}

