// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Descriptor::GetMessage(Communication	&com)
{
  if (inqueue.empty())
    return (false);
  com = inqueue.front();
  inqueue.pop_front();
  return (true);
}

