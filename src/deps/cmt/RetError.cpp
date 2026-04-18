// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include			"Communicator.hpp"

bpt::NetCom::Communication	&bpt::NetCom::Communicator::RetError(ErrorType		error,
								     unsigned int	time)
{
  this->communication.comtype = ERROR;
  this->communication.error.time = time;
  this->communication.error.errortype = error;
  return (this->communication);
}
