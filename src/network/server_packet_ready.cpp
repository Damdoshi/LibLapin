// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

bool			bunny_server_packet_ready(const t_bunny_server	*srv)
{
  bool			ret;

  ret = (((bpt::NetCom::Server*)srv->_private[1])->AnyFullPacket());
  scream_log_if("%p -> %s", "network", srv, ret ? "true" : "false");
  return (ret);
}
