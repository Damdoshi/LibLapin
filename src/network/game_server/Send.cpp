// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        <limits.h>
#include                        <vector>
#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            network::GameServer::Send
  (const Info                   &target,
   t_bunny_game_server_packet_type type,
   t_bunny_game_player_id       player,
   t_bunny_game_room_id         room,
   uint32_t                     code,
   const void                   *data,
   size_t                       size) const
{
  t_bunny_game_server_message  message;
  std::vector<char>            packet;
  size_t                       written;

  if (size > limits.max_payload_size || size > UINT32_MAX)
    return (false);
  try
    {
      packet.resize(sizeof(t_bunny_game_server_wire_packet) + size);
    }
  catch (...)
    {
      return (false);
    }
  message.type = type;
  message.service = service;
  message.player = player;
  message.room = room;
  message.code = code;
  message.data = data;
  message.size = size;
  if (!bunny_game_server_pack(packet.data(), packet.size(), &message, &written))
    return (false);
  return (bunny_network_write(GameServerInfo(target), packet.data(), written));
}

bool                            network::GameServer::Error
  (const Info                   &target,
   t_bunny_game_server_error    error,
   t_bunny_game_player_id       player,
   t_bunny_game_room_id         room) const
{
  return (Send(target, BGSP_ERROR, player, room, (uint32_t)error));
}

bool                            network::GameServer::NotifyRoom
  (const Room                   &room,
   t_bunny_game_server_packet_type type,
   t_bunny_game_player_id       player,
   bool                         include_player) const
{
  bool                          ok = true;

  for (auto id : room.players)
    {
      if (!include_player && id == player)
        continue;
      auto                      target = players.find(id);

      if (target == players.end())
        continue;
      ok = Send(target->second.info, type, player, room.id, 0) && ok;
    }
  return (ok);
}
