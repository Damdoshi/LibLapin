// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        <vector>
#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            network::GameServer::Remove(Player &player)
{
  const t_bunny_game_player_id  id = player.id;
  const Info                    info = player.info;
  std::vector<t_bunny_game_room_id> joined;
  bool                          ok = true;

  try
    {
      joined.assign(player.rooms.begin(), player.rooms.end());
    }
  catch (...)
    {
      return (false);
    }
  for (auto room : joined)
    ok = Leave(player, room, false) && ok;
  player_by_info.erase(info);
  players.erase(id);
  return (ok);
}

bool                            network::GameServer::Remove
  (t_bunny_game_player_id       id)
{
  auto                          player = players.find(id);

  if (player == players.end())
    return (false);
  return (Remove(player->second));
}

bool                            bunny_game_server_remove_player
  (t_bunny_game_server          *server,
   t_bunny_game_player_id       player)
{
  if (server == NULL)
    return (false);
  return (((network::GameServer*)server)->Remove(player));
}
