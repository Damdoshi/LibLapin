// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

void			bunny_delete_server(t_bunny_server		*srv)
{
  delete (bpt::NetCom::Server*)(srv->_private[1]);
  bunny_free(srv);
  scream_log_if("%p", "network", srv);
}
