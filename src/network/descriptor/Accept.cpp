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

  _socklen = sizeof(_sockaddr);
  if ((nfd = accept(fd, (struct sockaddr*)&_sockaddr, &_socklen)) == -1)
    return (NULL);
  if (cursize >= maxsize)
    {
      close(fd);
      return (NULL);
    }
  size_t		tmp;
  size_t		i;
  const network::Info	*inf;	

  for (i = 0; i < network->descriptors.size(); ++i)
    {
      if (!network->descriptors[i])
	{
	  Descriptor		&desc = network->descriptors[i];

	  inf = desc.Open(protocol, size, terminator, nfd, {_sockaddr, _socklen});
	  if (!inf)
	    goto Failure;
	  if (network->peers[*inf].AttachDescriptor(desc, inf) == false)
	    goto Close;
	  tmp = cursize;
	  if (!desc.Declare(fds, cursize, maxsize))
	    goto Detach;
	  return (&desc);
	}
    }
  return (NULL);
 Detach:
  cursize = tmp;
  network->peers[*inf].DetachDescriptor(network->descriptors[i]);
 Close:
  network->descriptors[i].Close();
 Failure:
  return (NULL);
}

