// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include	"Communicator.hpp"

void		bpt::NetCom::Communicator::Obsolete(void)
{
  this->communication.comtype = EXPIRED;
}
