// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            network::GameServer::Leave
  (Player                       &player,
   t_bunny_game_room_id         room_id,
   bool                         explicit_leave)
{
  auto                          room_it = rooms.find(room_id);

  if (room_it == rooms.end() ||
      room_it->second.players.find(player.id) == room_it->second.players.end())
    {
      if (explicit_leave)
        return (Error(player.info, BGSE_ROOM_NOT_JOINED, player.id, room_id));
      return (false);
    }
  Room                          &room = room_it->second;
  bool                          ok;

  if (limits.notify_members)
    ok = NotifyRoom(room, BGSP_PLAYER_LEFT, player.id, true);
  else if (explicit_leave)
    ok = Send(player.info, BGSP_PLAYER_LEFT, player.id, room_id, 0);
  else
    ok = true;
  room.players.erase(player.id);
  player.rooms.erase(room_id);
  if (room.players.empty())
    rooms.erase(room_it);
  return (ok);
}

bool                            network::GameServer::Leave
  (const Info                   &info,
   t_bunny_game_room_id         room_id)
{
  Player                        *player = FindPlayer(info);

  if (player == NULL)
    return (Error(info, BGSE_NOT_REGISTERED, 0, room_id));
  return (Leave(*player, room_id, true));
}
