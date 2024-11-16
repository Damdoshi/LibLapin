// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"

network::Descriptor	*network::Descriptor::Accept(struct pollfd	*fds,
						     size_t		&cursize,
						     size_t		maxsize) const
{
  struct sockaddr_in	_sockaddr;
  socklen_t		_socklen;
  int			nfd;

  if ((nfd = accept(fd, (struct sockaddr*)&_sockaddr, &_socklen)) == -1)
    return (NULL);
  if (cursize >= maxsize)
    {
      close(fd);
      return (NULL);
    }
  Descriptor		&ndesc = network.descriptors[network.nbr];

  ndesc.Open(protocol, size, terminator, 0, "", nfd);
  ndesc.Declare(fds, cursize, maxsize);
  return (&ndesc);
}

