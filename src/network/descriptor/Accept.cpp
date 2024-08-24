// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network.hpp"

network::Descriptor	*network::Descriptor::Accept(struct pollfd	*fds,
						     size_t		&cursize,
						     size_t		maxsize) const
{
  struct sockaddr_in	_sockaddr;
  socklen_t		_socklen;
  Descriptor		*ndesc;

  if ((ndesc = new (std::nothrow) Descriptor(network, protocol, size)) == NULL)
    return (NULL);
  if ((ndesc->fd = accept(fd, (struct sockaddr*)&_sockaddr, &_socklen)) == -1)
    return (NULL);
  memcpy(&ndesc->info.sockaddr, &_sockaddr, sizeof(ndesc->info.sockaddr));
  memcpy(&ndesc->info.socklen, &_socklen, sizeof(ndesc->info.socklen));
  if (ndesc->Declare(fds, cursize, maxsize) == false)
    {
      delete ndesc;
      return (NULL);
    }
  return (ndesc);
}

