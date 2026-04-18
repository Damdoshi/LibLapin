// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Server.hpp"

bool			bpt::NetCom::Server::KillClient(unsigned int	clt)
{
  std::list<Client*>::iterator	it;

  for (it = client.begin(); it != client.end() && (*it)->info->socket != clt; ++it);
  if (it != client.end())
    {
      this->Close((*it)->info->socket);
      delete *it;
      this->client.erase(it);
      return (true);
    }
  return (false);
}
