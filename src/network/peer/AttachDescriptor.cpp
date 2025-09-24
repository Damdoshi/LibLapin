// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Peer::AttachDescriptor(Descriptor	&desc,
						const ProtoSpec	&proto,
						const Info	*_info)
{
  if (descriptors.find(&desc) != descriptors.end())
    return (false);
  if (_info)
    info = *_info;
  descriptors.insert(&desc);
  protocol = proto;
  return (desc.AttachPeer(*this));
}

network::Peer	&network::Peer::operator<<(Descriptor		&desc)
{
  if (AttachDescriptor(desc, desc.protocol) == false)
    throw IOException("Cannot attach descriptor to peer");
  return (*this);
}
