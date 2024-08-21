// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network.hpp"

Descriptor		*network::Descriptor::Accept(struct pollfd	*fds,
						     size_t		&cursize,
						     size_t		maxsize) const
{
  struct sockaddr_in	_sockaddr;
  socklen_t		_socklen;
  Descriptor		*ndesc;

  if ((ndesc = new (std::nothrow) Descriptor(protocol, size)) == NULL)
    return (NULL);
  if ((ndesc->fd = accept(fd, &_socklen, &socklen_t)) == -1)
    return (NULL);
  memcpy(&ndesc->sockaddr, &_sockaddr, sizeof(ndesc->sockaddr));
  memcpy(&ndesc->socklen, &_socklen, sizeof(ndesc->socklen));
  if (ndesc->Declare(fds, cursize, maxsize) == false)
    {
      delete ndesc;
      return (NULL);
    }
  return (ndesc);
}

