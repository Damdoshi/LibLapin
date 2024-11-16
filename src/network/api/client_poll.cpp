// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			"deps/NetCom.hpp"
#include			"lapin_private.h"

const t_bunny_communication	*bunny_client_poll(t_bunny_client		*clt,
						   uint32_t			tmout)
{
  const t_bunny_communication	*com;

  com = (t_bunny_communication*)&(*(bpt::NetCom::Client*)clt->_private[1])(tmout);
  scream_log_if("%p client, %u timeout -> %p", "network", clt, tmout, com);
  return (com);
}

