// Jason Brillante
// Pentacle Technologie 2009-2012
//
// Network scheduler for TCP

#include		"Communicator.hpp"

bool			bpt::NetCom::operator==(const bpt::NetCom::Communication	&com,
						bpt::NetCom::ComType			comtype)
{
  return (com.comtype == comtype);
}
bool			bpt::NetCom::operator==(bpt::NetCom::ComType			comtype,
						const bpt::NetCom::Communication	&com)
{
  return (com.comtype == comtype);
}
