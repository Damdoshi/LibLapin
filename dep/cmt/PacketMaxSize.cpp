// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Communicator.hpp"

void			bpt::NetCom::Communicator::SetPacketMaxSize(unsigned int	x)
{
  this->max_size = x;
}

unsigned int		bpt::NetCom::Communicator::GetPacketMaxSize(void) const
{
  return (this->max_size);
}
