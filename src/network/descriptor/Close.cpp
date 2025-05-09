// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Descriptor::Close(void)
{
  if (fd == -1 || !active)
    return (false);
  for (auto it = associated_peers.begin(); it != associated_peers.end(); ++it)
    (*it)->DetachDescriptor(*this);
  associated_peers.clear();
  pollfd->fd *= -1;
  close(fd);
  fd = -1;
  active = false;
  doomed = false;

  // Si l'element qu'on ferme est le plus sur la droite dans le tableau
  if (network->nbr == position + 1)
    for (int i = position; i >= 0 && !network->descriptor[i]; --i)
      network->nbr -= 1;

  return (true);
}



