// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network/network.hpp"

void			network::Descriptor::Close(void)
{
  for (auto it = associated_peers.begin(); it != associated_peers.end(); ++it)
    (*it)->DetachDescriptor(*this);
  associated_peers.clear();
  if (fd != -1)
    close(fd);
  fd = -1;
}


