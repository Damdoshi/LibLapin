// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Server.hpp"

unsigned int		bpt::NetCom::Server::FindMaxFd(void)
{
  std::list<Client*>::iterator			i;
  unsigned int					max;

  max = this->master_info.socket;
  for (i = this->client.begin(); i != this->client.end(); ++i)
    if ((*i)->info->socket > max)
      max = (*i)->info->socket;
  return (max);
}
