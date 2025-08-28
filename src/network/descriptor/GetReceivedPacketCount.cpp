// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include		"lapin_private.h"

int			network::Descriptor::GetReceivedPacketCount(void) const
{
  return (inqueue.size());
}

