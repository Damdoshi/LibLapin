// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include	"lapin.h"
#include	"private/network/network.hpp"

void		network::Peer::SetProtocol(Protocol		_protocol,
					   size_t		_size,
					   char			_terminator,
					   int			_timeout,
					   bool			_resend)
{
  protocol.pcol_set = true;
  protocol.protocol = _protocol;
  protocol.size = _size;
  protocol.terminator = _terminator;
  protocol.timeout = _timeout;
  protocol.resend = _resend;
}

void		network::Peer::SetProtocol(ProtoSpec const	&spec)
{
  SetProtocol(spec.protocol, spec.size, spec.terminator, spec.timeout, spec.resend);
}

