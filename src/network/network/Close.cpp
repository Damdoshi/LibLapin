// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			Network::Close(const Info		&info)
{
  bool			closed = false;
  auto			it = peers.find(info);

  if (it != peers.end())
    {
      closed = it->second.Close() || closed;
      if (it->second.outqueue.empty() && it->second.rudp_pending.empty())
	peers.erase(it);
    }
  for (size_t i = 0; i < nbr; ++i)
    if (descriptors[i].info == info && descriptors[i].active)
      closed = descriptors[i].Close() || closed;
  return (closed);
}

