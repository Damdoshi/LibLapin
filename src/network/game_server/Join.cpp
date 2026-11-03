// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            network::GameServer::Join
  (const Info                   &info,
   t_bunny_game_room_id         room_id)
{
  Player                        *player = FindPlayer(info);

  if (player == NULL)
    return (Error(info, BGSE_NOT_REGISTERED, 0, room_id));
  if (room_id == 0)
    return (Error(info, BGSE_INVALID_ROOM, player->id, room_id));
  auto                          room_it = rooms.find(room_id);
  if (room_it == rooms.end())
    {
      if (rooms.size() >= limits.max_rooms)
        return (Error(info, BGSE_ROOM_LIMIT, player->id, room_id));
      Room                      room;

      room.id = room_id;
      try
        {
          room_it = rooms.emplace(room_id, room).first;
        }
      catch (...)
        {
          return (Error(info, BGSE_NETWORK_ERROR, player->id, room_id));
        }
    }
  Room                          &room = room_it->second;

  if (room.players.find(player->id) != room.players.end())
    return (Send(info, BGSP_PLAYER_JOINED, player->id, room_id, 0));
  if (room.players.size() >= limits.max_players_per_room)
    {
      if (room.players.empty())
        rooms.erase(room_it);
      return (Error(info, BGSE_ROOM_PLAYER_LIMIT, player->id, room_id));
    }
  try
    {
      room.players.insert(player->id);
      player->rooms.insert(room_id);
    }
  catch (...)
    {
      room.players.erase(player->id);
      player->rooms.erase(room_id);
      if (room.players.empty())
        rooms.erase(room_id);
      return (Error(info, BGSE_NETWORK_ERROR, player->id, room_id));
    }
  if (limits.notify_members)
    return (NotifyRoom(room, BGSP_PLAYER_JOINED, player->id, true));
  return (Send(info, BGSP_PLAYER_JOINED, player->id, room_id, 0));
}
