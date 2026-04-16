#include "lapin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_CLIENTS 1024
#define DEFAULT_FREQ 20
#define DEFAULT_INTERVAL_MS 1000
#define DEFAULT_COUNT 0
#define DEFAULT_FIXED_SIZE 64
#define DEFAULT_TCP_MAX (1024 * 1024)
#define DEFAULT_TERM_MAX 1460
#define DEFAULT_SIZE_MAX (1024 * 1024)

struct s_data
{
  t_bunny_network_info net;
  t_bunny_network_info clients[MAX_CLIENTS];
  int                  nbr_clients;

  t_bunny_protocol     pcol;
  bool                 verbose;
  bool                 hex_dump;

  bool                 has_local;
  int                  local_port;

  bool                 has_remote;
  char                 remote_ip[256];
  int                  remote_port;

  int                  payload_size;
  int                  send_count;   /* 0 = infini */
  int                  sent_count;
  int                  interval_ms;
  int64_t              next_send_ms;

  char                 message[1024];
};

static int64_t now_ms(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (int64_t)tv.tv_sec * 1000LL + (int64_t)(tv.tv_usec / 1000);
}

static const char *proto_name(t_bunny_protocol p)
{
  switch (p)
    {
    case BP_UDP_IMMEDIATE:       return "udp";
    case BP_TCP_IMMEDIATE:       return "tcp";
    case BP_UDP_RELIABLE:        return "rudp";
    case BP_TCP_FIXED_SIZE:      return "fixed";
    case BP_TCP_SIZED_PLUS_DATA: return "size";
    case BP_TCP_TERMINATED_DATA: return "term";
    default:                     return "unknown";
    }
}

static void hexdump(const void *data, size_t size)
{
  const unsigned char *d = (const unsigned char*)data;
  size_t i;

  for (i = 0; i < size; ++i)
    {
      printf("%02X", d[i]);
      if (i + 1 != size)
        printf(" ");
      if ((i % 16) == 15)
        printf("\n");
    }
  if (size % 16 != 0)
    printf("\n");
}

static void print_sockaddr(const char *prefix,
                           const struct sockaddr *sa,
                           socklen_t salen)
{
  char host[NI_MAXHOST];
  char serv[NI_MAXSERV];
  int r;

  if (sa == NULL || salen == 0)
    {
      printf("%s (null sockaddr)\n", prefix);
      return;
    }

  r = getnameinfo(sa,
                  salen,
                  host, sizeof(host),
                  serv, sizeof(serv),
                  NI_NUMERICHOST | NI_NUMERICSERV);
  if (r != 0)
    {
      printf("%s sockaddr_family=%d socklen=%u getnameinfo=%s\n",
             prefix,
             (int)sa->sa_family,
             (unsigned)salen,
             gai_strerror(r));
      return;
    }

  printf("%s %s:%s family=%d socklen=%u\n",
         prefix,
         host,
         serv,
         (int)sa->sa_family,
         (unsigned)salen);
}

static void print_info(const char *prefix, t_bunny_network_info info)
{
  if (info.socklen == 0)
    {
      printf("%s socklen=0\n", prefix);
      return;
    }

  print_sockaddr(prefix,
                 (const struct sockaddr*)&info.sockaddr,
                 (socklen_t)info.socklen);
}

static int find_client(struct s_data *vars, t_bunny_network_info info)
{
  int i;

  for (i = 0; i < vars->nbr_clients; ++i)
    if (memcmp(&vars->clients[i], &info, sizeof(info)) == 0)
      return i;
  return -1;
}

static t_bunny_response net_connect_cb(t_bunny_network_info info,
                                       t_bunny_event_state state,
                                       void *data)
{
  struct s_data *vars = (struct s_data*)data;
  int idx;

  idx = find_client(vars, info);

  if (state == DISCONNECTED)
    {
      if (idx >= 0)
        {
          printf("[CONNECT] peer %d disconnected\n", idx);
          if (vars->verbose)
            print_info("  peer:", info);
          vars->clients[idx] = vars->clients[vars->nbr_clients - 1];
          vars->nbr_clients -= 1;
        }
      else
        {
          printf("[CONNECT] unknown peer disconnected\n");
          if (vars->verbose)
            print_info("  peer:", info);
        }
      return GO_ON;
    }

  if (idx >= 0)
    {
      printf("[CONNECT] peer %d already known\n", idx);
      if (vars->verbose)
        print_info("  peer:", info);
      return GO_ON;
    }

  if (vars->nbr_clients >= MAX_CLIENTS)
    {
      fprintf(stderr, "[CONNECT] too many clients\n");
      return GO_ON;
    }

  vars->clients[vars->nbr_clients] = info;
  printf("[CONNECT] new peer %d\n", vars->nbr_clients);
  if (vars->verbose)
    print_info("  peer:", info);
  vars->nbr_clients += 1;
  return GO_ON;
}

static t_bunny_response message_cb(t_bunny_network_info info,
                                   void *buffer,
                                   size_t size,
                                   void *data)
{
  struct s_data *vars = (struct s_data*)data;
  int idx;

  idx = find_client(vars, info);

  printf("[MESSAGE] from peer %d, size=%zu\n", idx, size);
  if (vars->verbose)
    print_info("  peer:", info);

  if (vars->hex_dump)
    {
      hexdump(buffer, size);
    }
  else
    {
      fwrite(buffer, 1, size, stdout);
      if (size == 0 || ((char*)buffer)[size - 1] != '\n')
        printf("\n");
    }

  bunny_free(buffer);
  return GO_ON;
}

static int build_payload(struct s_data *vars, char *buffer, size_t buffer_size)
{
  int len;
  int i;

  if (vars->pcol == BP_TCP_FIXED_SIZE)
    {
      len = vars->payload_size > 0 ? vars->payload_size : DEFAULT_FIXED_SIZE;
      if ((size_t)len > buffer_size)
        len = (int)buffer_size;

      memset(buffer, 'A', (size_t)len);

      if (vars->message[0] != '\0')
        {
          size_t mlen = strlen(vars->message);
          if (mlen > (size_t)len)
            mlen = (size_t)len;
          memcpy(buffer, vars->message, mlen);
        }
      return len;
    }

  if (vars->payload_size > 0)
    {
      len = vars->payload_size;
      if ((size_t)len > buffer_size)
        len = (int)buffer_size;

      for (i = 0; i < len; ++i)
        buffer[i] = (char)('A' + (i % 26));

      if (vars->message[0] != '\0')
        {
          size_t mlen = strlen(vars->message);
          if (mlen > (size_t)len)
            mlen = (size_t)len;
          memcpy(buffer, vars->message, mlen);
        }
      return len;
    }

  if (vars->message[0] != '\0')
    len = snprintf(buffer, buffer_size, "%s\n", vars->message);
  else
    len = snprintf(buffer, buffer_size, "sent at %lld\n", (long long)now_ms());

  if (len < 0)
    len = 0;
  if ((size_t)len > buffer_size)
    len = (int)buffer_size;
  return len;
}

static void send_to_known_peers(struct s_data *vars, const void *buffer, size_t len)
{
  int i;

  if (vars->nbr_clients > 0)
    {
      for (i = 0; i < vars->nbr_clients; ++i)
        {
          bool r = bunny_network_write(vars->clients[i], buffer, len);
          printf("[SEND] peer %d size=%zu -> %s\n", i, len, r ? "OK" : "FAIL");
          if (vars->verbose)
            print_info("  peer:", vars->clients[i]);
        }
      return;
    }

  if (vars->net.socklen != 0)
    {
      bool r = bunny_network_write(vars->net, buffer, len);
      printf("[SEND] net size=%zu -> %s\n", len, r ? "OK" : "FAIL");
      if (vars->verbose)
        print_info("  net :", vars->net);
    }
  else
    {
      printf("[SEND] no network endpoint available\n");
    }
}

static t_bunny_response loop_cb(void *data)
{
  struct s_data *vars = (struct s_data*)data;
  int64_t now;
  char buffer[4096];
  int len;

  now = now_ms();

  if (vars->send_count > 0 && vars->sent_count >= vars->send_count)
    return GO_ON;

  if (now < vars->next_send_ms)
    return GO_ON;

  len = build_payload(vars, buffer, sizeof(buffer));
  send_to_known_peers(vars, buffer, (size_t)len);

  vars->sent_count += 1;
  vars->next_send_ms = now + vars->interval_ms;
  return GO_ON;
}

static int usage(const char *prog)
{
  fprintf(stderr,
          "Usage:\n"
          "  %s [-v] [--hex] -p proto [-L port] [-R ip port] [-s size] [-n count] [-i ms] [-m text]\n"
          "\n"
          "Protocols:\n"
          "  udp   tcp   rudp   fixed   size   term\n"
          "\n"
          "Examples:\n"
          "  %s -p tcp   -L 34567\n"
          "  %s -p tcp   -R 127.0.0.1 34567\n"
          "  %s -p term  -L 34570 -n 5 -i 500\n"
          "  %s -p fixed -L 34568 -s 64 --hex\n"
          "  %s -p udp   -L 34571\n"
          "  %s -p udp   -R 127.0.0.1 34571\n",
          prog, prog, prog, prog, prog, prog, prog);
  return 1;
}

int main(int argc, char **argv)
{
  static struct s_data vars;
  int i;
  int max;
  const char *open_ip = NULL;
  int open_port = 0;

  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IOLBF, 0);
 
  memset(&vars, 0, sizeof(vars));
  vars.pcol = BP_UDP_IMMEDIATE;
  vars.interval_ms = DEFAULT_INTERVAL_MS;
  vars.send_count = DEFAULT_COUNT;
  vars.payload_size = 0;
  vars.next_send_ms = now_ms() + vars.interval_ms;

  for (i = 1; i < argc; ++i)
    {
      if (strcmp(argv[i], "-v") == 0)
        {
          vars.verbose = true;
        }
      else if (strcmp(argv[i], "--hex") == 0)
        {
          vars.hex_dump = true;
        }
      else if (strcmp(argv[i], "-L") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          vars.has_local = true;
          vars.local_port = atoi(argv[++i]);
          if (vars.local_port <= 0 || vars.local_port > 65535)
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "-R") == 0)
        {
          if (i + 2 >= argc)
            return usage(argv[0]);
          vars.has_remote = true;
          strncpy(vars.remote_ip, argv[++i], sizeof(vars.remote_ip) - 1);
          vars.remote_ip[sizeof(vars.remote_ip) - 1] = '\0';
          vars.remote_port = atoi(argv[++i]);
          if (vars.remote_port <= 0 || vars.remote_port > 65535)
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "-p") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          ++i;
          if (strcasecmp(argv[i], "udp") == 0)
            vars.pcol = BP_UDP_IMMEDIATE;
          else if (strcasecmp(argv[i], "tcp") == 0)
            vars.pcol = BP_TCP_IMMEDIATE;
          else if (strcasecmp(argv[i], "rudp") == 0)
            vars.pcol = BP_UDP_RELIABLE;
          else if (strcasecmp(argv[i], "fixed") == 0)
            vars.pcol = BP_TCP_FIXED_SIZE;
          else if (strcasecmp(argv[i], "size") == 0)
            vars.pcol = BP_TCP_SIZED_PLUS_DATA;
          else if (strcasecmp(argv[i], "term") == 0)
            vars.pcol = BP_TCP_TERMINATED_DATA;
          else
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "-s") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          vars.payload_size = atoi(argv[++i]);
          if (vars.payload_size <= 0)
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "-n") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          vars.send_count = atoi(argv[++i]);
          if (vars.send_count < 0)
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "-i") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          vars.interval_ms = atoi(argv[++i]);
          if (vars.interval_ms <= 0)
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "-m") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          strncpy(vars.message, argv[++i], sizeof(vars.message) - 1);
          vars.message[sizeof(vars.message) - 1] = '\0';
        }
      else
        {
          return usage(argv[0]);
        }
    }

  if (vars.has_remote)
    {
      open_ip = vars.remote_ip;
      open_port = vars.remote_port;
    }
  else if (vars.has_local)
    {
      open_ip = NULL;
      open_port = vars.local_port;
    }
  else
    {
      return usage(argv[0]);
    }

  switch (vars.pcol)
    {
    case BP_TCP_IMMEDIATE:
      max = DEFAULT_TCP_MAX;
      break;
    case BP_TCP_FIXED_SIZE:
      max = vars.payload_size > 0 ? vars.payload_size : DEFAULT_FIXED_SIZE;
      break;
    case BP_TCP_SIZED_PLUS_DATA:
      max = vars.payload_size > 0 ? vars.payload_size : DEFAULT_SIZE_MAX;
      break;
    case BP_TCP_TERMINATED_DATA:
      max = vars.payload_size > 0 ? vars.payload_size : DEFAULT_TERM_MAX;
      break;
    case BP_UDP_IMMEDIATE:
    case BP_UDP_RELIABLE:
    default:
      max = vars.payload_size > 0 ? vars.payload_size : DEFAULT_SIZE_MAX;
      break;
    }

  printf("[OPEN] proto=%s max=%d term=%d local=%s:%d remote=%s:%d\n",
         proto_name(vars.pcol),
         max,
         '\v',
         vars.has_local ? "yes" : "no",
         vars.local_port,
         vars.has_remote ? vars.remote_ip : "no",
         vars.remote_port);

  vars.net = bunny_network_open(vars.pcol, max, '\v', 200, true, open_port, open_ip);
  if (vars.net.socklen == 0)
    {
      fprintf(stderr, "[OPEN] failed\n");
      return 1;
    }

  print_info("[OPEN] net:", vars.net);

  bunny_set_connect_response(net_connect_cb);
  bunny_set_message_response(message_cb);
  bunny_set_loop_main_function(loop_cb);
  bunny_loop(NULL, DEFAULT_FREQ, &vars);

  bunny_network_close(vars.net);
  return 0;
}


