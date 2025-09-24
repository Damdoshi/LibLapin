// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<string.h>
#include		<errno.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		"lapin.h"
#include		"private/network/network.hpp"

network::Info		Network::Descriptor::Open(const ProtoSpec	&specs,
						  uint16_t		_port,
						  const std::string	&_ip)
{
  unsigned int		tmp;

  if (active)
    Close();
  if (_ip == "")
    ip = htonl(INADDR_ANY);
  else if ((ip = inet_addr(_ip.c_str())) == 0)
    return (Info{});
  port = htons(_port);

  info.sockaddr.sin_family = AF_INET;
  info.sockaddr.sin_addr.s_addr = ip;
  info.sockaddr.sin_port = port;
  info.socklen = sizeof(info.sockaddr);

  if ((fd = socket(info.sockaddr.sin_family, !istcp(specs.protocol) ? SOCK_DGRAM : SOCK_STREAM, 0)) == -1)
    return (Info{});

  tmp = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));

  if (!istcp(specs.protocol))
    {
      tmp = 65536;
      setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp));
      setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &tmp, sizeof(tmp));
    }

  if (_ip == "")
    if (bind(fd, (struct sockaddr*)&info.sockaddr, info.socklen) == -1)
      goto CloseAndLeave;

  // TCP
  if (istcp(specs.protocol))
    {
      if (_ip == "")
	{
	  if (listen(fd, SOMAXCONN) == -1)
	    goto CloseAndLeave;
	}
      else
	{
	  if (connect(fd, (struct sockaddr*)&info.sockaddr, info.socklen) == -1)
	    goto CloseAndLeave;
	}
      if (specs.size == 0)
	protocol.size = BUNNY_NETWORK_MAXIMUM_PACKET_SIZE;
    }
  else if (specs.size == 0)
    protocol.size = 65507; // Maximum size of a UDP packet

  protocol = specs;
  active = true;
  doomed = false;
  return (info);
 CloseAndLeave:
  close(fd);
  return (Info{});
}

network::Info		network::Descriptor::Open(const ProtoSpec	&specs,
						  int			_fd,
						  network::Info		_info)
{
  if (active)
    Close();
  ip = _info.sockaddr.sin_addr.s_addr;
  port = ntohs(_info.sockaddr.sin_port);
  info = _info;
  fd = _fd;
  protocol = specs;
  active = true;
  doomed = false;
  return (info);
}
