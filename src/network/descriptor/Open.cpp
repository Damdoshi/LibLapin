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

const network::Info	*Network::Descriptor::Open(Protocol		_protocol,
						   size_t		_size,
						   char			_terminator,
						   uint16_t		_port,
						   const std::string	&_ip)
{
  unsigned int		tmp;

  if (active)
    Close();
  if (_ip == "")
    ip = htonl(INADDR_ANY);
  else if ((ip = inet_addr(_ip.c_str())) == 0)
    return (NULL);
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
    return (NULL);

  tmp = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));

  if (_protocol == IMMEDIATE_RETRIEVE)
    {
      tmp = 65536;
      setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp));
      setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &tmp, sizeof(tmp));
    }

  if (bind(fd, (struct sockaddr*)&info.sockaddr, info.socklen) == -1)
    goto CloseAndLeave;

  // TCP
  if (_protocol != IMMEDIATE_RETRIEVE)
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
    }
  
  size = _size;
  terminator = _terminator;
  protocol = _protocol;
  active = true;
  doomed = false;
  return (&info);
 CloseAndLeave:
  close(fd);
  return (NULL);
}

const network::Info	*network::Descriptor::Open(Protocol		_protocol,
						   size_t		_size,
						   char			_term,
						   int			_fd,
						   network::Info	_info)
{
  if (active)
    Close();
  ip = 0;
  port = 0;
  info = _info;
  fd = _fd;
  protocol = _protocol;
  size = _size;
  terminator = _term;
  active = true;
  doomed = false;
  return (&info);
}
