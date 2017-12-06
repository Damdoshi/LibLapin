// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

bool			bunny_server_write(t_bunny_server		*srv,
					   const void			*data,
					   size_t			len,
					   int				fd)
{
  bool			ret;

  ret = (((bpt::NetCom::Server*)srv->_private[1])->Write(data, len, fd));
  scream_log_if("%p server, %p data, %zu data length, %d fd -> %s",
		"network",
		srv, data, len, fd, ret ? "true" : "false");
  return (ret);
}

