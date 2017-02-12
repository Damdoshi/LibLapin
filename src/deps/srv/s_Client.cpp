// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include	<cstdlib>
#include	"Server.hpp"

bpt::NetCom::Server::s_Client::s_Client(bpt::NetCom::PacketProtocol	protocol)
  : info(NULL),
    buffer(NULL),
    cursor(NULL),
    size_received(0),
    protocol(protocol),
    doomed(false)
{
  packet_size.size = 0;
}

bpt::NetCom::Server::s_Client::~s_Client(void)
{
  WriteRequest	*wr;

  delete this->info;
  if (this->buffer != NULL && this->buffer != TOO_BIG)
    delete[] this->buffer;
  while (this->write_request.empty() == false)
    {
      wr = this->write_request.front();
      this->write_request.pop();
      delete wr;
    }
}
