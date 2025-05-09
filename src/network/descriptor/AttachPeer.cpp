// ************************************************
// 09/05/2025 13:48:41
// Keryan HOUSSIN 
// Bibliothèque Lapin
// ************************************************

#include		"lapin.h"
#include		"private/network/network.hpp"

bool			network::Descriptor::AttachPeer(Peer		&peer)
{
  if (associated_peers.find(&peer) != associated_peers.end())
    return (false);
  associated_peers.insert(&peer);
  return (true);   
}
