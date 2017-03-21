// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin.h"

void			bunny_delete_client(t_bunny_client		*clt)
{
  delete (bpt::NetCom::Client*)clt->_private[1];
  free((char*)clt->host);
  bunny_free(clt);
}
