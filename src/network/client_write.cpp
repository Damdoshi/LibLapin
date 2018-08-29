// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			"deps/NetCom.hpp"
#include			"lapin_private.h"

bool				bunny_client_write(t_bunny_client		*clt,
						   const void			*data,
						   size_t			len)
{
  bool				ret;

  ret = (((bpt::NetCom::Client*)clt->_private[1])->Write(data, len, clt->fd));
  scream_log_if("%p client, %p data, %zu data length -> %s", "network",
		clt, data, len, ret ? "true" : "false");
  return (ret);
}
