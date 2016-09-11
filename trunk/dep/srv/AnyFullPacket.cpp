// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Server.hpp"

bool			bpt::NetCom::Server::AnyFullPacket(void)
{
  std::list<Client*>::iterator	i;
  int			t;

  for (i = this->client.begin(); i != this->client.end(); ++i)
    if ((*i)->cursor - (*i)->buffer >= (t = (*i)->packet_size.size) && (*i)->cursor != UNUSED_BUFFER)
      return (true);
  return (false);
}
