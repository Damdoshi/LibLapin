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

  if (inbuffer)
    bunny_free(inbuffer);
  inbuffer_size = 0;
  rcursor = 0;
  spdbuffer = NULL;

  // On réarrange la taille du tableau si :
  //	- Il n'y a plus rien à lire (Sinon on le fera dans GetMessage)
  //    - Que le descriptor n'est plus actif
  //	- Que c'est l'élément le plus à droit du tableau
  if (!active && inqueue.empty() && network->nbr == position + 1)
    for (int i = position; i >= 0 && !network->descriptors[i]; --i)
      network->nbr -= 1;

  return (true);
}



