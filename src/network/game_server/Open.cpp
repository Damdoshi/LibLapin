// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        <string.h>
#include                        "lapin.h"
#include                        "private/network/game_server.hpp"


t_bunny_network_info            network::GameServer::Open
  (uint16_t port,
   int timeout,
   bool resend)
{
  t_bunny_network_info          info = bunny_network_open
    (BP_UDP_RELIABLE,
     sizeof(t_bunny_game_server_wire_packet) + limits.max_payload_size,
     0, timeout, resend, port, NULL);

  if (info.socklen != 0)
    {
      try
        {
          listeners.insert(GameServerInfo(info));
        }
      catch (...)
        {
          bunny_network_close(info);
          memset(&info, 0, sizeof(info));
        }
    }
  return (info);
}

bool                            network::GameServer::Close(const Info &listener)
{
  auto                          found = listeners.find(listener);

  if (found == listeners.end())
    return (false);
  bool                          closed = bunny_network_close(GameServerInfo(listener));

  listeners.erase(found);
  return (closed);
}

t_bunny_network_info            bunny_game_server_open
  (t_bunny_game_server          *server,
   uint16_t                     port,
   int                          timeout,
   bool                         resend)
{
  if (server == NULL)
    return (t_bunny_network_info{});
  return (((network::GameServer*)server)->Open(port, timeout, resend));
}

bool                            bunny_game_server_close
  (t_bunny_game_server          *server,
   t_bunny_network_info         listener)
{
  if (server == NULL)
    return (false);
  return (((network::GameServer*)server)->Close(network::GameServerInfo(listener)));
}
