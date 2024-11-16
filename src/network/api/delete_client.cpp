// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

void			bunny_delete_client(t_bunny_client		*clt)
{
  delete (bpt::NetCom::Client*)clt->_private[1];
  bunny_free((char*)clt->host);
  bunny_free(clt);
  scream_log_if("%p", "network", clt);
}
