// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include    "lapin_private.h"
#include		"Server.hpp"

bool			bpt::NetCom::Server::DoomClient(unsigned int	clt)
{
  std::list<Client*>::iterator	it;

  for (it = client.begin(); it != client.end() && (*it)->info->socket != clt; ++it);
  if (it != client.end())
    {
      (*it)->doomed = true;
      return (true);
    }
  bunny_errno = BE_CANNOT_FIND_ELEMENT;
  return (false);
}
