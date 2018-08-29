// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

bool			bunny_client_packet_ready(const t_bunny_client	*clt)
{
  bool			ret;

  ret = (((bpt::NetCom::Client*)clt->_private[1])->CheckFullPacket());
  scream_log_if("%p -> %s", "network", clt, ret ? "true" : "false");
  return (ret);
}
