// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"
#include	<iostream>

network::Peer::Peer(void)
{
  std::cout << "A new peer has been created !" << std::endl;
}

network::Peer::~Peer(void)
{
  std::set<Descriptor*>::iterator it;

  for (it = descriptors.begin(); it != descriptors.end(); ++it)
    (*it)->DetachPeer(*this);
}

