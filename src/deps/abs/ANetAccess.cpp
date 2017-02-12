// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
//

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
  std::map<unsigned int, bool>::iterator it = this->state.find(socket);

  if (it != this->state.end())
    this->state.erase(it);
}

void				bpt::NetAbs::INetAccess::WatchedSocket::Set(const Socket&	socket)
{
  this->state.insert(std::pair<unsigned int, bool>(socket, true));
}

bool				bpt::NetAbs::INetAccess::WatchedSocket::IsSet(const Socket&	socket)
{
  std::map<unsigned int, bool>::iterator it = this->state.find(socket);

  if (it != this->state.end())
    return (this->state[socket]);
  return false;
}

void				bpt::NetAbs::INetAccess::WatchedSocket::Clear(void)
{
  this->state.clear();
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
