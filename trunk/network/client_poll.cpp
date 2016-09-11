// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include			"dep/NetCom.hpp"
#include			"lapin.h"

const t_bunny_communication	*bunny_client_poll(t_bunny_client		*clt,
						   uint32_t			tmout)
{
  return ((t_bunny_communication*)&(*(bpt::NetCom::Client*)clt->_private)(tmout));
}

