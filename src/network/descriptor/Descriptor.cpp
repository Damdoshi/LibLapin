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
#include		"private/network/network.hpp"

network::Descriptor::Descriptor(Network			&_network)
  : network(_network),
    pollfd(NULL),
    protocol(IMMEDIATE_RETRIEVE),
    size(-1),
    terminator(0),
    active(false),
    doomed(false),
    fd(-1),
    ip(0),
    port(0),
    wcursor(0),
    rcursor(0),
    spdbuffer(NULL)
{}

/*

network::Descriptor::Descriptor(Network			&_network,
				Protocol		_protocol,
				size_t			_size,
				char			_terminator,
				uint16_t		_port,
				const std::string	&_ip)
  : Descriptor(_network, -1, _protocol, _size, _terminator)
{
  unsigned int		tmp;

  if (_ip == "")
    ip = htonl(INADDR_ANY);
  else if ((ip = inet_addr(_ip.c_str())) == 0)
    throw std::logic_error("Invalid IP");
  port = htons(_port);

  info.sockaddr.sin_family = AF_INET;
  info.sockaddr.sin_addr.s_addr = ip;
  info.sockaddr.sin_port = port;
  info.socklen = sizeof(info.sockaddr);

  if (_protocol == IMMEDIATE_RETRIEVE)
    fd = socket(info.sockaddr.sin_family, SOCK_DGRAM, 0);
  else
    fd = socket(info.sockaddr.sin_family, SOCK_STREAM, 0);
  if (fd == -1)
    goto Leave;

  tmp = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));

  if (_protocol == IMMEDIATE_RETRIEVE)
    {
      tmp = 65536;
      setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp));
      setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &tmp, sizeof(tmp));
    }

  if (_ip != "")
    {
      if (bind(fd, (struct sockaddr*)&info.sockaddr, info.socklen) == -1)
	goto CloseAndLeave;
      if (_protocol != IMMEDIATE_RETRIEVE
	  && listen(fd, SOMAXCONN) == -1)
	goto CloseAndLeave;
    }
  else if (_protocol != IMMEDIATE_RETRIEVE
	   && connect(fd, (struct sockaddr*)&info.sockaddr, info.socklen) == -1)
    goto CloseAndLeave;

  memset(info.identity, 0, sizeof(info.identity));
  return ;
 CloseAndLeave:
  close(fd);
 Leave:
  throw std::runtime_error(std::string("Cannot achieve Descriptor's construction. ") + strerror(errno));
}

network::Descriptor::Descriptor(Network		&_network,
				int		_fd,
				Protocol	_protocol,
				size_t		_size,
				char		_terminator)
  : network(_network),
    pollfd(NULL),
    protocol(_protocol),
    size(_size),
    terminator(_terminator),
    active(_fd != -1),
    doomed(false),
    fd(_fd),
    wcursor(0),
    rcursor(0),
    spdbuffer(NULL)
{
  if (size < 16)
    size = 16;
  inbuffer.resize(size);
  spdbuffer = (size_plus_data*)&inbuffer[0];
  memset(info.identity, 0, sizeof(info.identity));
}

*/

network::Descriptor::~Descriptor(void)
{
  Close();
}

