// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

bool		network::Descriptor::GetMessage(Communication	&com)
{
  if (inqueue.empty())
    return (false);
  com = std::move(inqueue.front());
  inqueue.pop_front();

  // On réarrange la taille du tableau si :
  //	- Il n'y a plus rien à lire
  //    - Que le descriptor n'est plus actif
  //	- Que c'est l'élément le plus à droit du tableau
  if (!active && inqueue.empty() && network->nbr == position + 1)
    for (int i = position; i >= 0 && !network->descriptors[i]; --i)
      network->nbr -= 1;

  return (true);
}

