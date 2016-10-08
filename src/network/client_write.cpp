// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include			"dep/NetCom.hpp"
#include			"lapin.h"

bool				bunny_client_write(t_bunny_client		*clt,
						   const void			*data,
						   size_t			len)
{
  return (((bpt::NetCom::Client*)clt->_private)->Write(data, len, clt->fd));
}

