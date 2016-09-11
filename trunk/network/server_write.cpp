// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"dep/NetCom.hpp"
#include		"lapin.h"

bool			bunny_server_write(t_bunny_server		*srv,
					   const void			*data,
					   size_t			len,
					   int				fd)
{
  return (((bpt::NetCom::Server*)srv->_private)->Write(data, len, fd));
}

