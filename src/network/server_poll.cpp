// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include			"deps/NetCom.hpp"
#include			"lapin_private.h"

const t_bunny_communication	*bunny_server_poll(t_bunny_server		*srv,
						   uint32_t			tmout)
{
  const t_bunny_communication	*ret;

  ret = ((t_bunny_communication*)&(*(bpt::NetCom::Server*)srv->_private[1])(tmout));
  scream_log_if("%p server, %u timeout -> %p", srv, tmout, ret);
  return (ret);
}
