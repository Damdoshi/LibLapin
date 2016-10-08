// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include	<string.h>
#include	"Communicator.hpp"

char		bpt::NetCom::EOC[3] =
  {
    '\r',
    '\n',
    '\0'
  };

const bpt::NetCom::Communication	&bpt::NetCom::Communicator::GetCommunication(void) const
{
  return (this->communication);
}

bool					bpt::NetCom::Communicator::IsInit(void) const
{
  return (this->init);
}

bpt::NetCom::Communicator::Communicator(const std::string	&port,
					unsigned int		max_size,
					unsigned int		chunk_size)
  : port(port),
    max_size(max_size),
    chunk_size(chunk_size),
    init(false),
    protocol(SIZABLE)
{
  memset(&this->communication, 0, sizeof(this->communication));
}

bpt::NetCom::Communicator::Communicator(bpt::NetCom::PacketProtocol	protocol,
					const std::string		&port,
					unsigned int			max_size,
					unsigned int			chunk_size)
  : port(port),
    max_size(max_size),
    chunk_size(chunk_size),
    init(false),
    protocol(protocol)
{
  memset(&this->communication, 0, sizeof(this->communication));
}

bpt::NetCom::Communicator::~Communicator(void)
{}
