// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include			"Server.hpp"

bpt::NetCom::Communication	&bpt::NetCom::Server::Disconnected(unsigned int	usr,
								   unsigned int	time)
{
  std::list<Client*>::iterator	it;

  this->communication.comtype = DISCONNECTED;
  this->communication.disconnected.time = time;
  this->communication.disconnected.client = usr;
  for (it = this->client.begin(); it != this->client.end() && (*it)->info->socket != usr; ++it);
  if (it != this->client.end())
    {
      delete *it;
      this->client.erase(it);
    }
  return (this->communication);
}
