// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include	<cstdlib>
#include	"Server.hpp"

bool		bpt::NetCom::Server::Start(const std::string	&port)
{
  if (this->init == true)
    this->Stop();
  else
    this->init = true;
  this->port = port;
  if (OpenSocket(NetAbs::INetAccess::TCP, this->master_info, port) == false)
    return (false);
  if (Bind(this->master_info) == false)
    return (false);
  if (Listen(this->master_info) == false)
    return (false);
  return (true);
}

bool		bpt::NetCom::Server::Stop(void)
{
  std::list<Client*>::iterator	i;
  bool				suc;

  suc = true;
  this->init = false;
  for (i = this->client.begin(); i != this->client.end(); ++i)
    {
      if (Close((*i)->info->socket) == false)
	suc = false;
      delete *i;
    }
  if (Close(this->master_info.socket) == false)
    return (false);
  return (suc);
}

bpt::NetCom::Server::Server(const std::string	&port) throw (int)
  : Communicator(port)
{
  if (port != "")
    if (this->Start(port) == false)
      throw 0;
}

bpt::NetCom::Server::Server(bpt::NetCom::PacketProtocol	protocol,
			    const std::string		&port) throw (int)
  : Communicator(protocol, port)
{
  if (port != "")
    if (this->Start(port) == false)
      throw 0;
}

bpt::NetCom::Server::~Server(void)
{
  if (this->init)
    this->Stop();
}
