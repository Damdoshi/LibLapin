// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

size_t                          network::GameServer::PlayerCount(void) const
{
  return (players.size());
}

size_t                          network::GameServer::RoomCount(void) const
{
  return (rooms.size());
}

size_t                          network::GameServer::RoomPlayerCount
  (t_bunny_game_room_id         id) const
{
  auto                          room = rooms.find(id);

  if (room == rooms.end())
    return (0);
  return (room->second.players.size());
}

bool                            network::GameServer::HasPlayer
  (t_bunny_game_player_id       id) const
{
  return (players.find(id) != players.end());
}

bool                            network::GameServer::PlayerIsInRoom
  (t_bunny_game_player_id       id,
   t_bunny_game_room_id         room_id) const
{
  auto                          player = players.find(id);

  if (player == players.end())
    return (false);
  return (player->second.rooms.find(room_id) != player->second.rooms.end());
}

size_t                          bunny_game_server_player_count
  (const t_bunny_game_server    *server)
{
  if (server == NULL)
    return (0);
  return (((const network::GameServer*)server)->PlayerCount());
}

size_t                          bunny_game_server_room_count
  (const t_bunny_game_server    *server)
{
  if (server == NULL)
    return (0);
  return (((const network::GameServer*)server)->RoomCount());
}

size_t                          bunny_game_server_room_player_count
  (const t_bunny_game_server    *server,
   t_bunny_game_room_id         room)
{
  if (server == NULL)
    return (0);
  return (((const network::GameServer*)server)->RoomPlayerCount(room));
}

bool                            bunny_game_server_has_player
  (const t_bunny_game_server    *server,
   t_bunny_game_player_id       player)
{
  if (server == NULL)
    return (false);
  return (((const network::GameServer*)server)->HasPlayer(player));
}

bool                            bunny_game_server_player_is_in_room
  (const t_bunny_game_server    *server,
   t_bunny_game_player_id       player,
   t_bunny_game_room_id         room)
{
  if (server == NULL)
    return (false);
  return (((const network::GameServer*)server)->PlayerIsInRoom(player, room));
}
