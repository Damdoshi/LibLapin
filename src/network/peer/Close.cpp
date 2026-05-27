// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			network::Peer::Close(void)
{
  std::set<Descriptor*> copy = descriptors;

  descriptors.clear();
  for (auto it = copy.begin(); it != copy.end(); ++it)
    {
      (*it)->associated_peers.erase(this);
      if (istcp((*it)->protocol))
	(*it)->Close();
    }
  outqueue.clear();
  rudp_pending.clear();
  doomed = true;
  return (true);
}

