// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026

#include                        <limits.h>
#include                        <string.h>
#include                        "lapin.h"
#include                        "private/network/game_server.hpp"

bool                            bunny_game_server_pack
  (void                         *buffer,
   size_t                       buffer_size,
   const t_bunny_game_server_message *message,
   size_t                       *written_size)
{
  if (buffer == NULL || message == NULL ||
      (message->data == NULL && message->size != 0) ||
      message->size > UINT32_MAX)
    return (false);
  const size_t total = sizeof(t_bunny_game_server_wire_packet) + message->size;

  if (buffer_size < total)
    return (false);
  t_bunny_game_server_wire_packet *packet =
    (t_bunny_game_server_wire_packet*)buffer;

  memset(packet, 0, sizeof(*packet));
  packet->magic = htonl(BUNNY_GAME_SERVER_MAGIC);
  packet->version = BUNNY_GAME_SERVER_VERSION;
  packet->type = (uint8_t)message->type;
  packet->header_size = htons((uint16_t)sizeof(*packet));
  packet->service = network::HostToNetwork64(message->service);
  packet->player = network::HostToNetwork64(message->player);
  packet->room = network::HostToNetwork64(message->room);
  packet->payload_size = htonl((uint32_t)message->size);
  packet->code = htonl(message->code);
  if (message->size)
    memcpy(packet->payload, message->data, message->size);
  if (written_size != NULL)
    *written_size = total;
  return (true);
}

bool                            bunny_game_server_unpack
  (const void                   *buffer,
   size_t                       buffer_size,
   t_bunny_game_server_message  *message)
{
  if (buffer == NULL || message == NULL ||
      buffer_size < sizeof(t_bunny_game_server_wire_packet))
    return (false);
  const t_bunny_game_server_wire_packet *packet =
    (const t_bunny_game_server_wire_packet*)buffer;
  const uint16_t header_size = ntohs(packet->header_size);
  const uint32_t payload_size = ntohl(packet->payload_size);

  if (ntohl(packet->magic) != BUNNY_GAME_SERVER_MAGIC ||
      packet->version != BUNNY_GAME_SERVER_VERSION ||
      header_size < sizeof(*packet) || header_size > buffer_size ||
      payload_size > buffer_size - header_size ||
      (size_t)header_size + payload_size != buffer_size)
    return (false);
  message->type = (t_bunny_game_server_packet_type)packet->type;
  message->service = network::NetworkToHost64(packet->service);
  message->player = network::NetworkToHost64(packet->player);
  message->room = network::NetworkToHost64(packet->room);
  message->code = ntohl(packet->code);
  message->data = &((const char*)buffer)[header_size];
  message->size = payload_size;
  return (true);
}
