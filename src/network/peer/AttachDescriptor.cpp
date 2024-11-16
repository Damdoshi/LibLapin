// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"private/network/network.hpp"

bool		network::Peer::AttachDescriptor(Descriptor	&desc)
{
  if (descriptors.contains(desc))
    return (false);
  descriptors.insert(desc);
  return (true);
}

network::Peer	&network::Peer::operator<<(Descriptor		&desc)
{
  if (AttachDescriptor(desc) == false)
    throw IOException("Cannot attach descriptor to peer");
  return (*this);
}
