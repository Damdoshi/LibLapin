// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Server.hpp"

/// Peut certainement s'ameliorer en retirant la creation locale de client
//  puis la copie par une creation et modification directement dans la liste

unsigned int		bpt::NetCom::Server::NewClient(void)
{
  Client		*clt;

  clt = new Client(this->protocol);
  clt->info = new NetAbs::INetAccess::Info();
  if (Accept(this->master_info, *clt->info) == NULL)
    return (UMAX);
  this->client.push_back(clt);
  return (clt->info->socket);
}
