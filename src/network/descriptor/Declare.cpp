// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network.hpp"

bool			network::Descriptor::Declare(struct pollfd	*fds,
						     size_t		&cursize,
						     size_t		maxsize) const
{
  if (cursize >= maxsize)
    return (false);
  if (!active || doomed || fd == -1)
    return (false);
  pollfd = &fds[cursize++];
  pollfd->fd = fd;
  pollfd->events = POLLIN;
  if (outqueue.size())
    pollfd->events |= POLLOUT;
  return (true);
}

