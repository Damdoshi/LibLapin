// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"dep/NetCom.hpp"
#include		"lapin.h"

bool			bunny_server_packet_ready(const t_bunny_server	*srv)
{
  return (((bpt::NetCom::Server*)srv->_private)->AnyFullPacket());
}

