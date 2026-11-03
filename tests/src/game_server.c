#include                        <arpa/inet.h>
#include                        <assert.h>
#include                        <string.h>
#include                        "lapin.h"

static t_bunny_network_info     make_info(uint16_t port)
{
  t_bunny_network_info         info = {0};

  info.sockaddr.sin_family = AF_INET;
  info.sockaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  info.sockaddr.sin_port = htons(port);
  info.socklen = sizeof(info.sockaddr);
  return (info);
}

static size_t                   make_packet(char *buffer,
                                            size_t buffer_size,
                                            t_bunny_game_server_packet_type type,
                                            uint64_t service,
                                            uint64_t player,
                                            uint64_t room,
                                            const void *data,
                                            size_t size)
{
  t_bunny_game_server_message  message = {
    .type = type,
    .service = service,
    .player = player,
    .room = room,
    .code = 0,
    .data = data,
    .size = size
  };
  size_t                       written = 0;

  assert(bunny_game_server_pack(buffer, buffer_size, &message, &written));
  return (written);
}

static bool                     handle(t_bunny_game_server *server,
                                       t_bunny_network_info info,
                                       char *packet,
                                       size_t packet_size)
{
  t_bunny_communication        communication = {
    .comtype = BCT_MESSAGE,
    .info = info,
    .data = packet,
    .size = packet_size
  };

  return (bunny_game_server_handle(server, &communication));
}

int                             main(void)
{
  t_bunny_game_server_limits   limits = {
    .max_players = 8,
    .max_rooms = 4,
    .max_players_per_room = 4,
    .max_payload_size = 1024,
    .echo_sender = false,
    .notify_members = true
  };
  t_bunny_game_server         *server = bunny_new_game_server(12, &limits);
  t_bunny_network_info        alice = make_info(10001);
  t_bunny_network_info        bob = make_info(10002);
  char                        packet[256];
  size_t                      size;

  assert(server != NULL);

  size = make_packet(packet, sizeof(packet), BGSP_REGISTER, 12, 101, 0, NULL, 0);
  assert(handle(server, alice, packet, size));
  assert(bunny_game_server_player_count(server) == 1);
  assert(bunny_game_server_has_player(server, 101));

  size = make_packet(packet, sizeof(packet), BGSP_JOIN_ROOM, 12, 0, 7, NULL, 0);
  assert(handle(server, alice, packet, size));
  assert(bunny_game_server_room_count(server) == 1);
  assert(bunny_game_server_room_player_count(server, 7) == 1);
  assert(bunny_game_server_player_is_in_room(server, 101, 7));

  size = make_packet(packet, sizeof(packet), BGSP_REGISTER, 12, 202, 0, NULL, 0);
  assert(handle(server, bob, packet, size));
  size = make_packet(packet, sizeof(packet), BGSP_JOIN_ROOM, 12, 0, 7, NULL, 0);
  assert(handle(server, bob, packet, size));
  assert(bunny_game_server_room_player_count(server, 7) == 2);

  size = make_packet(packet, sizeof(packet), BGSP_MULTICAST, 12, 0, 7, "abc", 3);
  assert(handle(server, alice, packet, size));

  t_bunny_communication disconnected = {
    .comtype = BCT_NETDISCONNECTED,
    .info = bob
  };
  assert(bunny_game_server_handle(server, &disconnected));
  assert(!bunny_game_server_has_player(server, 202));
  assert(bunny_game_server_room_player_count(server, 7) == 1);

  size = make_packet(packet, sizeof(packet), BGSP_LEAVE_ROOM, 12, 0, 7, NULL, 0);
  assert(handle(server, alice, packet, size));
  assert(bunny_game_server_room_count(server) == 0);

  size = make_packet(packet, sizeof(packet), BGSP_REGISTER, 99, 303, 0, NULL, 0);
  assert(!handle(server, alice, packet, size));

  bunny_delete_game_server(server);
  return (EXIT_SUCCESS);
}
