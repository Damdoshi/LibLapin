// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"dep/NetCom.hpp"
#include		"lapin.h"

bool			bunny_server_doom_client(t_bunny_server		*srv,
						 int			fd)
{
  return (((bpt::NetCom::Server*)srv->_private)->DoomClient(fd));
}

