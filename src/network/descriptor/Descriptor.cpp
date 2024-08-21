// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<string.h>
#include		<errno.h>
#include		"private/network.hpp"

network::Descriptor::Descriptor(Protocol		_protocol,
				size_t			_size,
				uint16_t		_port,
				const std::string	&_ip)
  : Descriptor(-1, _protocol, _size)
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

  if (_protocol == IMMEDIATE_RETURN)
    fd = socket(info.sockaddr.sin_family, SOCK_DGRAM, 0);
  else
    fd = socket(info.sockaddr_sin.family, SOCK_STREAM, 0);
  if (fd == -1)
    goto Leave;

  tmp = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));

  if (_protocol == IMMEDIATE_RETURN)
    {
      tmp = 65536;
      setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp));
      setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &tmp, sizeof(tmp));
    }

  if (_ip != "")
    {
      if (bind(fd, (struct sockaddr*)&info.sockaddr, info.socklen) == -1)
	goto CloseAndLeave;
      if (_protocol != IMMEDIATE_RETURN
	  && listen(fd, SOMAXCONN) == -1)
	goto CloseAndLeave;
    }
  else if (_protocol != IMMEDIATE_RETURN
	   && connect(fd, (struct sockaddr*)&info.sockaddr, info.socklen) == -1)
    goto CloseAndLeave;

  return ;
 CloseAndLeave:
  close(fd);
 Leave:
  throw std::runtime_error("Cannot achieve Descriptor's construction. {}", strerror(errno));
}

network::Descriptor::Descriptor(int		_fd,
				Protocol	_protocol,
				size_t		_size)
  : protocol(_protocol),
    size(_size),
    active(_fd != -1),
    doomed(false),
    fd(_fd),
    polllfd(NULL),
    wcursor(0),
    rcursor(0),
    spdbuffer(NULL)
{
  if (size < 16)
    size = 16;
  inbuffer.resize(size);
  spdbuffer = &inbuffer[0];
  memset(identity, 0, sizeof(identity));
}

network::Descriptor::~Descriptor(void)
{
  Close();
}

