// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include			"lapin_private.h"

t_bunny_network_info		bunny_network_open(t_bunny_protocol	pcol,
						   size_t		size,
						   char			term,
						   int			tmout,
						   uint16_t		port,
						   const char		*ip)
{
  if (!ip)
    ip = "";
  return (gl_network.Open((Network::Protocol)pcol, size, term, tmout, port, ip));
}

