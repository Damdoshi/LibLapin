// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
//

#include			<sys/select.h>
#include			<iostream>
#include			"ANetAccess.hpp"

bpt::NetAbs::ANetAccess::Info	*bpt::NetAbs::ANetAccess::NewInfo(void)
{
  Info				*info;

  info = new Info;
  infolist.push_back(info);
  return (info);
}

void				bpt::NetAbs::INetAccess::WatchedSocket::Clear(const Socket&	socket)
{
  FD_CLR(socket, &state);
}

void				bpt::NetAbs::INetAccess::WatchedSocket::Set(const Socket&	socket)
{
  FD_SET(socket, &state);
}

bool				bpt::NetAbs::INetAccess::WatchedSocket::IsSet(const Socket&	socket)
{
  return (FD_ISSET(socket, &state));
}

void				bpt::NetAbs::INetAccess::WatchedSocket::Clear(void)
{
  FD_ZERO(&state);
}

bpt::NetAbs::ANetAccess::ANetAccess(void)
{}

bpt::NetAbs::ANetAccess::~ANetAccess(void)
{
  while (infolist.empty() != true)
    {
      delete infolist.front();
      infolist.pop_front();
    }
}
