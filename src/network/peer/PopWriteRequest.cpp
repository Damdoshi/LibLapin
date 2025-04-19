// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Peer::PopWriteRequest(void)
{
  if (outqueue.empty())
    return (false);
  outqueue.pop_front();
  return (true);
}

