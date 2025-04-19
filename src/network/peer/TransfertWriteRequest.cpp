// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Peer::TransfertWriteRequest(void)
{
  auto		it = descriptors.begin();
  size_t	max = rand() % descriptors.size();

  for (size_t i = 0; i < max; ++i)
    ++it;
  network::WriteRequest	&wr = outqueue.front();
  
  return ((*it)->SetMessage(wr.data.data(), wr.data.size(), info, wr.wt, wr.wtdata));
}

