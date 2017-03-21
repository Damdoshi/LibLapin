// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include	<cstdlib>
#include	"Client.hpp"
#include	"To.hpp"

bool		bpt::NetCom::Client::Start(const std::string			&host,
					   const std::string			&port,
					   NetAbs::INetAccess::Protocol		prot)
{
  if (this->init == true)
    this->Stop();
  this->host = host;
  this->port = port;
  if (OpenSocket(prot, this->master_info, port, host) == false)
    return (false);
  if (Connect(this->master_info) == false)
    return (false);
  this->packet_size.size = 0;
  this->size_received = 0;
  this->init = true;
  return (true);
}

bool		bpt::NetCom::Client::Stop(void)
{
  this->init = false;
  while (this->write_request.empty() == false)
    {
      delete this->write_request.front();
      this->write_request.pop();
    }
  if (Close(this->master_info.socket) == false)
    return (false);
  return (true);
}

bpt::NetCom::Client::Client(const std::string		&host,
			    const std::string		&port) throw (int)
  : Communicator(port),
    buffer(NULL),
    cursor(NULL)
{
  if (host == "" || port == "")
    return;
  if (this->Start(host, port) == false)
    throw 0;
}

bpt::NetCom::Client::Client(bpt::NetCom::PacketProtocol	protocol,
			    const std::string		&host,
			    const std::string		&port) throw (int)
  : Communicator(protocol, port),
    buffer(NULL),
    cursor(NULL)
{
  if (host == "" || port == "")
    return;
  if (this->Start(host, port) == false)
    throw 0;
}

bpt::NetCom::Client::~Client(void)
{
  if (this->init)
    this->Stop();
}
