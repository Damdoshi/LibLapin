// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        "lapin.h"
#include                        "private/network/game_server.hpp"
#include                        "private/network/reliable_udp.hpp"

network::GameServer::GameServer
  (uint64_t _service,
   const t_bunny_game_server_limits *_limits)
  : service(_service)
{
  limits.max_players = 4096;
  limits.max_rooms = 1024;
  limits.max_players_per_room = 256;
  limits.max_payload_size = 60 * 1024;
  limits.echo_sender = false;
  limits.notify_members = true;
  if (_limits != NULL)
    limits = *_limits;
  if (limits.max_players == 0)
    limits.max_players = 1;
  if (limits.max_rooms == 0)
    limits.max_rooms = 1;
  if (limits.max_players_per_room == 0)
    limits.max_players_per_room = 1;

  const size_t udp_limit = 65507 - sizeof(ReliableUdpHeader) -
    sizeof(t_bunny_game_server_wire_packet);

  if (limits.max_payload_size == 0 || limits.max_payload_size > udp_limit)
    limits.max_payload_size = udp_limit;
}

network::GameServer::~GameServer(void)
{
  for (auto listener : listeners)
    bunny_network_close(GameServerInfo(listener));
}

t_bunny_game_server             *bunny_new_game_server
  (uint64_t                     service,
   const t_bunny_game_server_limits *limits)
{
  try
    {
      return ((t_bunny_game_server*)new network::GameServer(service, limits));
    }
  catch (...)
    {
      return (NULL);
    }
}

void                            bunny_delete_game_server(t_bunny_game_server *server)
{
  delete (network::GameServer*)server;
}
