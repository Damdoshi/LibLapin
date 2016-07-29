// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include	"Server.hpp"

unsigned int	bpt::NetCom::Server::GetIP(unsigned int	fd)
{
  std::list<Client*>::iterator	it;

  for (it = client.begin(); it != client.end() && (*it)->info->socket != fd; ++it);
  if (it != client.end())
    return ((*it)->info->ip);
  return (0);
}
