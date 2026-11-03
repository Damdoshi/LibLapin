// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            network::GameServer::Relay
  (const Info                   &info,
   t_bunny_game_room_id         room_id,
   const void                   *data,
   size_t                       size)
{
  Player                        *source = FindPlayer(info);

  if (source == NULL)
    return (Error(info, BGSE_NOT_REGISTERED, 0, room_id));
  if (size > limits.max_payload_size)
    return (Error(info, BGSE_PAYLOAD_TOO_LARGE, source->id, room_id));
  auto                          room = rooms.find(room_id);
  if (room == rooms.end() ||
      room->second.players.find(source->id) == room->second.players.end())
    return (Error(info, BGSE_ROOM_NOT_JOINED, source->id, room_id));
  return (Multicast(room_id, source->id, data, size));
}

bool                            network::GameServer::Multicast
  (t_bunny_game_room_id         room_id,
   t_bunny_game_player_id       sender,
   const void                   *data,
   size_t                       size) const
{
  if ((data == NULL && size != 0) || size > limits.max_payload_size)
    return (false);
  auto                          room = rooms.find(room_id);
  bool                          ok = true;

  if (room == rooms.end())
    return (false);
  for (auto id : room->second.players)
    {
      if (!limits.echo_sender && sender != 0 && id == sender)
        continue;
      auto                      player = players.find(id);

      if (player == players.end())
        continue;
      ok = Send(player->second.info, BGSP_MESSAGE, sender, room_id, 0, data, size) && ok;
    }
  return (ok);
}

bool                            bunny_game_server_multicast
  (t_bunny_game_server          *server,
   t_bunny_game_room_id         room,
   t_bunny_game_player_id       sender,
   const void                   *data,
   size_t                       size)
{
  if (server == NULL)
    return (false);
  return (((network::GameServer*)server)->Multicast(room, sender, data, size));
}
