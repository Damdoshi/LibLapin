// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include			"dep/NetCom.hpp"
#include			"lapin.h"

const t_bunny_communication	*bunny_server_poll(t_bunny_server		*srv,
						   uint32_t			tmout)
{
  return ((t_bunny_communication*)&(*(bpt::NetCom::Server*)srv->_private)(tmout));
}

