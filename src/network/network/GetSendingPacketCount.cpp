// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

int			Network::GetSendingPacketCount(void) const
{
  int			ret = 0;
  
  for (auto it = descriptors.begin(); it != descriptors.end(); ++it)
    ret += it->second->GetSendingPacketCount();
  return (ret);
}




