// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<poll.h>
#include		"lapin.h"
#include		"private/network/network.hpp"

void			Network::Descriptor::Doom(void)
{
  doomed = true;
  if (pollfd != NULL)
    {
      pollfd->events &= ~POLLIN;
      if (outqueue.empty())
	pollfd->events &= ~POLLOUT;
    }
}

