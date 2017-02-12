// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

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
  return (false);
}
