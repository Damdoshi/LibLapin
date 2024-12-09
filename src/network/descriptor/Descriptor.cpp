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
  : network(&_network),
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

