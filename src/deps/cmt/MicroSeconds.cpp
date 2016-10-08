// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Communicator.hpp"

unsigned int		bpt::NetCom::Communicator::MicroSeconds(struct timeval	*now,
								struct timeval	*before)
{
  return ((now->tv_sec * 1000000 + now->tv_usec) - (before->tv_sec * 1000000 + before->tv_usec));
}
