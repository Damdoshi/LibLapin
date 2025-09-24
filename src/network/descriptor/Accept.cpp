// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.h"
#include		<arpa/inet.h>


network::Info		network::Descriptor::Accept(size_t			&cursize,
						    size_t			maxsize)
{
  struct sockaddr_in	_sockaddr;
  socklen_t		_socklen;
  int			nfd;

  _socklen = sizeof(_sockaddr);
  if ((nfd = accept(fd, (struct sockaddr*)&_sockaddr, &_socklen)) == -1)
    return (Info{});
  if (cursize >= maxsize)
    {
      close(nfd);
      return (Info{});
    }

  network::Info		inf;
  size_t		tmp;
  size_t		i;

  for (i = 0; i < network->descriptors.size(); ++i)
    if (!network->descriptors[i])
      {
	network::Info	tmpInfo(_sockaddr, _socklen);

	if (!(inf = network->descriptors[i].Open(protocol, nfd, tmpInfo)))
	  goto Failure;
	if (network->peers[inf].AttachDescriptor(network->descriptors[i], protocol, &inf) == false)
	  goto Close;
	tmp = cursize;
	if (!network->descriptors[i].Declare())
	  goto Detach;
	if (i == cursize)
	  cursize++;
	// Préviens la connexion d'un client
	inqueue.push_back(Communication{inf, true});
	return (inf);
      }
  return (Info{});
 Detach:
  cursize = tmp;
  network->peers[inf].DetachDescriptor(network->descriptors[i]);
 Close:
  network->descriptors[i].Close();
 Failure:
  return (Info{});
}

