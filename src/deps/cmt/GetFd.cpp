// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"NetCom.hpp"

int			bpt::NetCom::Communicator::GetFd(void) const
{
  return (master_info.socket);
}

