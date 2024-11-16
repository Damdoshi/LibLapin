// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include		"private/network/network.hpp"

network::Peer::operator	bool (void) const
{
  return (descriptors.size());
}

network::Peer::operator	const Info & (void) const
{
  return (info);
}

network::Peer::operator	int (void) const
{
  retrn (outqueue.size());
}

