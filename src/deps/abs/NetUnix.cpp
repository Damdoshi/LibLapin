// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// LibLapin

#include		<unistd.h>
#include		<limits.h>
#include		<cstdlib>
#include		"NetUnix.hpp"

bool			bpt::NetAbs::NetUnix::OpenSocket(Protocol		protocol,
							 Info			&master_info,
							 const std::string	&port,
							 const std::string	&ip) const
{
  struct protoent	*proto;
  unsigned int		type;
  const char		*protoname[UDP + 1] = {
    "TCP",
    "UDP"
  };

  if (protocol != UDP)
    type = SOCK_STREAM;
  else
    type = SOCK_DGRAM;
  if ((proto = getprotobyname(protoname[protocol])) == NULL)
    return (false);
  if (protocol == UNIX)
    {
      if ((master_info.socket = socket(AF_UNIX, type, proto->p_proto)) == UMAX)
	return (false);
    }
  else if ((master_info.socket = socket(AF_INET, type, proto->p_proto)) == UMAX)
    return (false);
  master_info.port = htons(atoi(port.c_str()));
  if (ip.compare("") != 0)
    master_info.ip = inet_addr(ip.c_str());
  else
    master_info.ip = htonl(INADDR_ANY);
  type = 1;
#ifndef             __WIN32
  if (setsockopt(master_info.socket, SOL_SOCKET, SO_REUSEADDR, &type, sizeof(type)) == -1)
    return (false);
#else
  if (setsockopt(master_info.socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&type, sizeof(type)) == -1)
    return (false);
#endif
  return (true);
}

bool			bpt::NetAbs::NetUnix::Bind(const Info			&master_info) const
{
  struct sockaddr_in	sockaddr;

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = master_info.ip;
  sockaddr.sin_port = master_info.port;
  if (bind(master_info.socket, (struct sockaddr*)&sockaddr, (socklen_t)sizeof(sockaddr)) == -1)
    return (false);
  return (true);
}

bool			bpt::NetAbs::NetUnix::Listen(const Info			&master_info) const
{
  if (listen(master_info.socket, SOMAXCONN) == 60)
    return (false);
  return (true);
}

bpt::NetAbs::INetAccess::Info *bpt::NetAbs::NetUnix::Accept(const Info		&master_info,
							    Info		&info) const
{
  struct sockaddr_in	sockaddr;
  unsigned int		len;

  len = sizeof(sockaddr);
  if ((len = accept(master_info.socket, (struct sockaddr*)&sockaddr, (socklen_t*)&len)) == UMAX)
    return (NULL);
  info.socket = len;
  info.ip = sockaddr.sin_addr.s_addr;
  info.port = sockaddr.sin_port;
  return (&info);
}

bool			bpt::NetAbs::NetUnix::Connect(const Info		&info) const
{
  struct sockaddr_in	sockaddr;

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_port = info.port;
  sockaddr.sin_addr.s_addr = info.ip;
  if (connect(info.socket, (struct sockaddr*)&sockaddr, (socklen_t)sizeof(sockaddr)) == -1)
    return (false);
  return (true);
}

unsigned int		bpt::NetAbs::NetUnix::RecvFrom(const Info		&master_info,
						       char			*buffer,
						       unsigned int		len,
						       Info			*info) const
{
  struct sockaddr_in	sockaddr;
  unsigned int		l;

  l = sizeof(sockaddr);
  sockaddr.sin_family = AF_INET;
  if ((l = recvfrom(master_info.socket, buffer, len, 0, (struct sockaddr*)&sockaddr, (socklen_t*)&l)) == UINT_MAX)
    return (UMAX);
  if (info != NULL)
    {
      info->ip = sockaddr.sin_addr.s_addr;
      info->port = sockaddr.sin_port;
    }
  return (l);
}

unsigned int		bpt::NetAbs::NetUnix::SendTo(const Info			&master_info,
						     const char			*buffer,
						     unsigned int		len,
						     const Info			*info) const
{
  struct sockaddr_in	sockaddr;
  unsigned int		l;

#ifndef			__WIN32
# define		_LOCALFLAG		MSG_NOSIGNAL
#else
# define		_LOCALFLAG		0
#endif

  sockaddr.sin_family = AF_INET;
  if (info != NULL)
    {
      sockaddr.sin_addr.s_addr = info->ip;
      sockaddr.sin_port = info->port;
      if ((l = sendto(master_info.socket, buffer, len, _LOCALFLAG, (struct sockaddr*)&sockaddr, (socklen_t)sizeof(sockaddr))) == UINT_MAX)
	return (UMAX);
      return (l);
    }
  if ((l = send(master_info.socket, buffer, len, _LOCALFLAG)) == UINT_MAX)
    return (UMAX);
  return (l);

#undef			_LOCALFLAG
}

int			bpt::NetAbs::NetUnix::Select(Socket			max,
						     WatchedSocket		*read,
						     WatchedSocket		*write,
						     WatchedSocket		*except,
						     Delay			*delay) const
{
  std::map<unsigned int, bool>::iterator	it;
  struct timeval		tim;

  if (delay != NULL)
    {
      tim.tv_sec = delay->seconds;
      tim.tv_usec = delay->microseconds;
      return (select(max, &read->state, &write->state, &except->state, &tim));
    }
  return (select(max, &read->state, &write->state, &except->state, NULL));
}

bool			bpt::NetAbs::NetUnix::Close(Socket  &socket) const
{
  if (close(socket) == -1)
    return (false);
  return (true);
}

bpt::NetAbs::NetUnix::NetUnix()
    : ANetAccess()
{}

bpt::NetAbs::NetUnix::~NetUnix()
{}

