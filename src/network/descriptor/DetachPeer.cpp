// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin.h"
#include		"private/network/network.hpp"

int			network::Descriptor::DetachPeer(const Peer	&peer)
{
  associated_peers.erase((network::Peer*)&peer);
  ((network::Peer*)&peer)->descriptors.erase(this);
  // Si on fait du TCP
  if (istcp(protocol))
    Close();
  return (associated_peers.size());
}
