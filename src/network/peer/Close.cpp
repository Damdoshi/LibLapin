// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			network::Peer::Close(void)
{
  std::set<Descriptor*>::iterator it;

  for (it = descriptors.begin(); it != descriptors.end(); ++it)
    (*it)->DetachPeer(*this);
  doomed = true;
  return (true);
}

