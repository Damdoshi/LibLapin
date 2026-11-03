// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

network::GameServer::Player     *network::GameServer::FindPlayer(const Info &info)
{
  auto                          index = player_by_info.find(info);

  if (index == player_by_info.end())
    return (NULL);
  auto                          player = players.find(index->second);
  if (player == players.end())
    return (NULL);
  return (&player->second);
}

const network::GameServer::Player *network::GameServer::FindPlayer(const Info &info) const
{
  auto                          index = player_by_info.find(info);

  if (index == player_by_info.end())
    return (NULL);
  auto                          player = players.find(index->second);
  if (player == players.end())
    return (NULL);
  return (&player->second);
}
