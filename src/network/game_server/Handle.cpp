// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        <string.h>
#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            network::GameServer::Handle
  (const t_bunny_communication  &communication)
{
  Info                          info = GameServerInfo(communication.info);

  if (communication.comtype == BCT_NETDISCONNECTED)
    {
      Player                    *player = FindPlayer(info);

      if (player == NULL)
        return (false);
      Remove(*player);
      return (true);
    }
  if (communication.comtype != BCT_MESSAGE || communication.data == NULL)
    return (false);
  if (communication.size < sizeof(uint32_t))
    return (false);

  uint32_t                      magic;
  memcpy(&magic, communication.data, sizeof(magic));
  if (ntohl(magic) != BUNNY_GAME_SERVER_MAGIC)
    return (false);
  if (communication.size < sizeof(t_bunny_game_server_wire_packet))
    return (true);

  const t_bunny_game_server_wire_packet *wire =
    (const t_bunny_game_server_wire_packet*)communication.data;
  const uint64_t                packet_service = NetworkToHost64(wire->service);

  if (packet_service != service)
    return (false);
  if (wire->version != BUNNY_GAME_SERVER_VERSION)
    {
      Error(info, BGSE_BAD_VERSION);
      return (true);
    }

  t_bunny_game_server_message  message;

  if (!bunny_game_server_unpack(communication.data, communication.size, &message) ||
      !GameServerPacketTypeIsRequest(message.type))
    {
      Error(info, BGSE_BAD_PACKET);
      return (true);
    }
  switch (message.type)
    {
    case BGSP_REGISTER:
      Register(info, message.player);
      break;
    case BGSP_JOIN_ROOM:
      Join(info, message.room);
      break;
    case BGSP_LEAVE_ROOM:
      Leave(info, message.room);
      break;
    case BGSP_MULTICAST:
      Relay(info, message.room, message.data, message.size);
      break;
    case BGSP_QUIT:
      {
        Player                  *player = FindPlayer(info);

        if (player == NULL)
          Error(info, BGSE_NOT_REGISTERED);
        else
          Remove(*player);
        break;
      }
    default:
      Error(info, BGSE_BAD_PACKET);
      break;
    }
  return (true);
}

bool                            bunny_game_server_handle
  (t_bunny_game_server          *server,
   const t_bunny_communication  *communication)
{
  if (server == NULL || communication == NULL)
    return (false);
  return (((network::GameServer*)server)->Handle(*communication));
}
