// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin.h"

bool			bunny_client_packet_ready(const t_bunny_client	*clt)
{
  return (((bpt::NetCom::Client*)clt->_private[1])->CheckFullPacket());
}
