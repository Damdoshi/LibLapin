// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network/network.hpp"

int			network::Descriptor::DetachPeer(const Peer	&peer)
{
  associated_peers.erase((network::Peer*)&peer);
  // Si on fait du TCP
  if (protocol != IMMEDIATE_RETRIEVE)
    Close();
  return (associated_peers.size());
}
