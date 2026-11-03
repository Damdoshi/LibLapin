// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            network::GameServer::Register
  (const Info                   &info,
   t_bunny_game_player_id       id)
{
  Player                        *already = FindPlayer(info);

  if (id == 0)
    return (Error(info, BGSE_INVALID_PLAYER));
  if (already != NULL)
    {
      if (already->id == id)
        return (Send(info, BGSP_REGISTERED, id, 0, 0));
      return (Error(info, BGSE_ALREADY_REGISTERED, already->id));
    }
  if (players.find(id) != players.end())
    return (Error(info, BGSE_PLAYER_ID_IN_USE, id));
  if (players.size() >= limits.max_players)
    return (Error(info, BGSE_PLAYER_LIMIT, id));

  Player                        player;

  player.id = id;
  player.info = info;
  try
    {
      players.emplace(id, player);
      player_by_info.emplace(info, id);
    }
  catch (...)
    {
      players.erase(id);
      player_by_info.erase(info);
      return (Error(info, BGSE_NETWORK_ERROR, id));
    }
  return (Send(info, BGSP_REGISTERED, id, 0, 0));
}
