// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"private/network/network.hpp"

network::Peer	&network::Peer::operator=(const Info		&_info)
{
  info = _info;
  return (*this);
}

