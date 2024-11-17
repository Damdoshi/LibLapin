// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

Network::Network(void)
  : descriptors(*this),
    nbr(0)
{
  memset(pollfd, 0, sizeof(pollfd));
}

Network::~Network(void)
{}

