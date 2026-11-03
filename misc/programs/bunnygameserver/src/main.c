// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Standalone neutral RUDP game relay.

#include                        <errno.h>
#include                        <signal.h>
#include                        <stdint.h>
#include                        <stdio.h>
#include                        <stdlib.h>
#include                        <string.h>
#include                        "lapin.h"

#define MAX_LISTENERS           64

static volatile sig_atomic_t    keep_running = 1;

static void                     stop_server(int sig)
{
  (void)sig;
  keep_running = 0;
}

static void                     usage(const char *program)
{
  fprintf(stderr,
          "Usage: %s [options]\n"
          "  -p PORT        Add a RUDP listening port (repeatable)\n"
          "  -s SERVICE     Logical service identifier (default: 0)\n"
          "  -t MSECONDS    RUDP peer timeout (default: 5000)\n"
          "  --players N    Maximum registered players\n"
          "  --rooms N      Maximum rooms\n"
          "  --members N    Maximum players per room\n"
          "  --payload N    Maximum opaque payload size\n"
          "  --echo         Relay messages back to their sender\n"
          "  --no-presence  Do not broadcast join/leave notifications\n"
          "  --no-resend    Disable RUDP retransmission\n"
          "  -h, --help     Display this help\n",
          program);
}

static int                      parse_u64(const char *str, uint64_t *value)
{
  char                         *end;
  unsigned long long           parsed;

  errno = 0;
  parsed = strtoull(str, &end, 0);
  if (errno != 0 || end == str || *end != '\0')
    return (0);
  *value = (uint64_t)parsed;
  return (1);
}

static int                      parse_size(const char *str, size_t *value)
{
  uint64_t                     parsed;

  if (!parse_u64(str, &parsed) || parsed > SIZE_MAX)
    return (0);
  *value = (size_t)parsed;
  return (1);
}

static int                      parse_port(const char *str, uint16_t *port)
{
  uint64_t                     parsed;

  if (!parse_u64(str, &parsed) || parsed == 0 || parsed > UINT16_MAX)
    return (0);
  *port = (uint16_t)parsed;
  return (1);
}

int                             main(int argc, char **argv)
{
  uint16_t                     ports[MAX_LISTENERS];
  size_t                       port_count = 0;
  uint64_t                     service = 0;
  int                          timeout = 5000;
  int                          resend = 1;
  t_bunny_game_server_limits   limits = {
    .max_players = 4096,
    .max_rooms = 1024,
    .max_players_per_room = 256,
    .max_payload_size = 60 * 1024,
    .echo_sender = false,
    .notify_members = true
  };

  for (int i = 1; i < argc; ++i)
    {
      if ((!strcmp(argv[i], "-h")) || (!strcmp(argv[i], "--help")))
        {
          usage(argv[0]);
          return (EXIT_SUCCESS);
        }
      if (!strcmp(argv[i], "--echo"))
        limits.echo_sender = true;
      else if (!strcmp(argv[i], "--no-presence"))
        limits.notify_members = false;
      else if (!strcmp(argv[i], "--no-resend"))
        resend = 0;
      else if ((!strcmp(argv[i], "-p")) && i + 1 < argc)
        {
          if (port_count >= MAX_LISTENERS || !parse_port(argv[++i], &ports[port_count]))
            {
              fprintf(stderr, "Invalid listening port.\n");
              return (EXIT_FAILURE);
            }
          port_count += 1;
        }
      else if ((!strcmp(argv[i], "-s")) && i + 1 < argc)
        {
          if (!parse_u64(argv[++i], &service))
            {
              fprintf(stderr, "Invalid service identifier.\n");
              return (EXIT_FAILURE);
            }
        }
      else if ((!strcmp(argv[i], "-t")) && i + 1 < argc)
        {
          uint64_t parsed;

          if (!parse_u64(argv[++i], &parsed) || parsed > INT32_MAX)
            {
              fprintf(stderr, "Invalid timeout.\n");
              return (EXIT_FAILURE);
            }
          timeout = (int)parsed;
        }
      else if ((!strcmp(argv[i], "--players")) && i + 1 < argc)
        {
          if (!parse_size(argv[++i], &limits.max_players))
            return (fprintf(stderr, "Invalid player limit.\n"), EXIT_FAILURE);
        }
      else if ((!strcmp(argv[i], "--rooms")) && i + 1 < argc)
        {
          if (!parse_size(argv[++i], &limits.max_rooms))
            return (fprintf(stderr, "Invalid room limit.\n"), EXIT_FAILURE);
        }
      else if ((!strcmp(argv[i], "--members")) && i + 1 < argc)
        {
          if (!parse_size(argv[++i], &limits.max_players_per_room))
            return (fprintf(stderr, "Invalid room member limit.\n"), EXIT_FAILURE);
        }
      else if ((!strcmp(argv[i], "--payload")) && i + 1 < argc)
        {
          if (!parse_size(argv[++i], &limits.max_payload_size))
            return (fprintf(stderr, "Invalid payload limit.\n"), EXIT_FAILURE);
        }
      else
        {
          fprintf(stderr, "Unknown or incomplete option: %s\n", argv[i]);
          usage(argv[0]);
          return (EXIT_FAILURE);
        }
    }

  if (port_count == 0)
    ports[port_count++] = 0x6279;

  t_bunny_game_server          *server = bunny_new_game_server(service, &limits);
  if (server == NULL)
    {
      fprintf(stderr, "Cannot allocate game server.\n");
      return (EXIT_FAILURE);
    }

  for (size_t i = 0; i < port_count; ++i)
    {
      t_bunny_network_info listener = bunny_game_server_open
        (server, ports[i], timeout, resend != 0);

      if (listener.socklen == 0)
        {
          fprintf(stderr, "Cannot open RUDP listener on port %hu.\n", ports[i]);
          bunny_delete_game_server(server);
          return (EXIT_FAILURE);
        }
      printf("Listening on UDP port %hu for service %llu.\n",
             ports[i], (unsigned long long)service);
    }

  signal(SIGINT, stop_server);
  signal(SIGTERM, stop_server);

  while (keep_running)
    {
      double remaining = bunny_network_poll(20.0);

      if (remaining != remaining)
        {
          fprintf(stderr, "Network polling failed.\n");
          break;
        }
      while (bunny_network_inbox() > 0)
        {
          t_bunny_communication communication = bunny_network_read();

          bunny_game_server_handle(server, &communication);
          if (communication.data != NULL)
            bunny_free(communication.data);
        }
    }

  printf("Stopping: %zu player(s), %zu room(s).\n",
         bunny_game_server_player_count(server),
         bunny_game_server_room_count(server));
  bunny_delete_game_server(server);
  return (EXIT_SUCCESS);
}
