// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Peer::DetachDescriptor(const Descriptor &desc)
{
  bool		result = descriptors.erase((Descriptor*)&desc);

  if (descriptors.size() == 0)
    Close();
  return (result);
}

network::Peer	&network::Peer::operator>>(const Descriptor	&desc)
{
  if (DetachDescriptor(desc) == false)
    throw IOException("Cannot detach descriptor from peer");
  return (*this);
}
