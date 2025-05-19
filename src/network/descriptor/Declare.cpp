// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<poll.h>
#include		"lapin.h"
#include		"private/network/network.hpp"

bool			network::Descriptor::Declare(void)
{
  if (!active || doomed || fd == -1)
    return (false);
  pollfd->fd = fd;
  pollfd->events = POLLIN;
  if (outqueue.size())
    pollfd->events |= POLLOUT;
  return (true);
}

