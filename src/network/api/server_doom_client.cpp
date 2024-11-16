// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

bool			bunny_server_doom_client(t_bunny_server		*srv,
						 int			fd)
{
  bool			ret;

  ret = (((bpt::NetCom::Server*)srv->_private[1])->DoomClient(fd));
  scream_log_if("%p server, %d fd -> %s", "network", srv, fd, ret ? "true" : "false");
  return (ret);
}
