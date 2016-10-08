// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include			"Client.hpp"

bpt::NetCom::Communication	&bpt::NetCom::Client::Disconnected(unsigned int	time)
{
  this->communication.comtype = DISCONNECTED;
  this->communication.disconnected.time = time;
  this->communication.disconnected.client = this->master_info.socket;
  return (this->communication);
}
