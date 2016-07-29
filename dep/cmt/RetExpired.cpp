// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include			"Communicator.hpp"

bpt::NetCom::Communication	&bpt::NetCom::Communicator::RetExpired(unsigned int	time)
{
  this->communication.comtype = EXPIRED;
  this->communication.expired.time = time;
  return (this->communication);
}
