// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	<set>
#include	"lapin_private.h"

network::Peer::Peer(void)
{}

network::Peer::~Peer(void)
{
  std::set<Descriptor*> copy = descriptors;

  descriptors.clear();
  for (auto it = copy.begin(); it != copy.end(); ++it)
    (*it)->associated_peers.erase(this);
}

