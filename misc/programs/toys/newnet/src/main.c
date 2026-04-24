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
#include <signal.h>

#define MAX_CLIENTS 1024
#define DEFAULT_FREQ 20
#define DEFAULT_INTERVAL_MS 1000
#define DEFAULT_COUNT 0
#define DEFAULT_FIXED_SIZE 64
#define DEFAULT_TCP_MAX (1024 * 1024)
#define DEFAULT_TERM_MAX 1460
#define DEFAULT_SIZE_MAX (1024 * 1024)
#define DEFAULT_UDP_MAX 1472
#define DEFAULT_RUDP_MAX 1472

typedef struct s_peer_stats
{
  t_bunny_network_info info;
  int                  connected;
  int64_t              first_seen_ms;
  int64_t              last_seen_ms;
  int                  sent_ok;
  int                  sent_fail;
  int                  received_messages;
  size_t               sent_bytes;
  size_t               received_bytes;
  int                  seq_seen;
  int                  last_seq;
  int                  seq_duplicates;
  int                  seq_gaps;
  int                  seq_regressions;
} t_peer_stats;

struct s_data
{
  t_bunny_network_info net;
  t_peer_stats         clients[MAX_CLIENTS];
  int                  nbr_clients;

  t_bunny_protocol     pcol;
  bool                 verbose;
  bool                 hex_dump;
  bool                 quiet_payload;
  bool                 sequence_payload;

  bool                 has_local;
  int                  local_port;

  bool                 has_remote;
  char                 remote_ip[256];
  int                  remote_port;

  int                  payload_size;
  int                  send_count;   /* 0 = infini */
  int                  sent_count;    /* tours où au moins un envoi a réussi */
  int                  build_seq;
  int                  send_attempts;
  int                  send_ok;
  int                  send_fail;
  int                  send_skipped;
  bool                 no_send;
  int                  duration_ms;
  int                  first_send_delay_ms;
  int                  received_messages;
  size_t               sent_bytes;
  size_t               received_bytes;
  int                  interval_ms;
  int                  loop_freq;
  int64_t              next_send_ms;
  int64_t              start_ms;

  char                 message[1024];
};

static volatile sig_atomic_t g_stop_requested = 0;

static void handle_signal(int sig)
{
  (void)sig;
  g_stop_requested = 1;
}

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
    if (bunny_infocmp(vars->clients[i].info, info) == 0)
      return i;
  return -1;
}

static int register_client(struct s_data *vars,
                           t_bunny_network_info info,
                           const char *origin,
                           bool connected)
{
  int idx;
  int64_t now;

  idx = find_client(vars, info);
  if (idx >= 0)
    {
      vars->clients[idx].last_seen_ms = now_ms();
      if (connected)
        vars->clients[idx].connected = 1;
      return idx;
    }

  if (vars->nbr_clients >= MAX_CLIENTS)
    {
      fprintf(stderr, "[PEER] too many clients while registering from %s\n", origin);
      return -1;
    }

  idx = vars->nbr_clients++;
  now = now_ms();
  memset(&vars->clients[idx], 0, sizeof(vars->clients[idx]));
  vars->clients[idx].info = info;
  vars->clients[idx].connected = connected ? 1 : 0;
  vars->clients[idx].first_seen_ms = now;
  vars->clients[idx].last_seen_ms = now;

  printf("[PEER] registered peer %d from=%s connected=%s\n",
         idx,
         origin,
         connected ? "yes" : "no");
  if (vars->verbose)
    print_info("  peer:", info);

  return idx;
}

static void unregister_client(struct s_data *vars, int idx)
{
  if (idx < 0 || idx >= vars->nbr_clients)
    return;
  printf("[PEER] removed peer %d\n", idx);
  if (idx + 1 != vars->nbr_clients)
    vars->clients[idx] = vars->clients[vars->nbr_clients - 1];
  vars->nbr_clients -= 1;
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
          unregister_client(vars, idx);
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
      vars->clients[idx].connected = 1;
      vars->clients[idx].last_seen_ms = now_ms();
      printf("[CONNECT] peer %d already known\n", idx);
      if (vars->verbose)
        print_info("  peer:", info);
      return GO_ON;
    }

  idx = register_client(vars, info, "connect", true);
  if (idx >= 0)
    printf("[CONNECT] new peer %d\n", idx);
  return GO_ON;
}


static void inspect_sequence(struct s_data *vars,
                             int idx,
                             const void *buffer,
                             size_t size)
{
  const char *str;
  char *end;
  long seq;

  if (!vars->sequence_payload || idx < 0 || size < 5)
    return;
  str = (const char*)buffer;
  if (memcmp(str, "SEQ:", 4) != 0)
    return;

  seq = strtol(str + 4, &end, 10);
  if (end == str + 4 || *end != ':')
    return;
  if (seq < 0 || seq > 2147483647L)
    return;

  if (!vars->clients[idx].seq_seen)
    {
      vars->clients[idx].seq_seen = 1;
      vars->clients[idx].last_seq = (int)seq;
      printf("[SEQ] peer %d first=%ld\n", idx, seq);
      return;
    }

  if ((int)seq == vars->clients[idx].last_seq)
    {
      vars->clients[idx].seq_duplicates += 1;
      printf("[SEQ] peer %d duplicate=%ld\n", idx, seq);
    }
  else if ((int)seq < vars->clients[idx].last_seq)
    {
      vars->clients[idx].seq_regressions += 1;
      printf("[SEQ] peer %d regression previous=%d current=%ld\n",
             idx, vars->clients[idx].last_seq, seq);
      vars->clients[idx].last_seq = (int)seq;
    }
  else
    {
      if ((int)seq != vars->clients[idx].last_seq + 1)
        {
          vars->clients[idx].seq_gaps += (int)seq - vars->clients[idx].last_seq - 1;
          printf("[SEQ] peer %d gap previous=%d current=%ld missing=%d\n",
                 idx,
                 vars->clients[idx].last_seq,
                 seq,
                 (int)seq - vars->clients[idx].last_seq - 1);
        }
      vars->clients[idx].last_seq = (int)seq;
    }
}

static t_bunny_response message_cb(t_bunny_network_info info,
                                   void *buffer,
                                   size_t size,
                                   void *data)
{
  struct s_data *vars = (struct s_data*)data;
  int idx;

  idx = find_client(vars, info);
  if (idx < 0)
    idx = register_client(vars, info, "message", false);

  if (idx >= 0)
    {
      vars->clients[idx].last_seen_ms = now_ms();
      vars->clients[idx].received_messages += 1;
      vars->clients[idx].received_bytes += size;
    }
  vars->received_messages += 1;
  vars->received_bytes += size;

  inspect_sequence(vars, idx, buffer, size);

  printf("[MESSAGE] from peer %d, size=%zu\n", idx, size);
  if (vars->verbose)
    print_info("  peer:", info);

  if (vars->quiet_payload)
    {
      /* Payload volontairement masqué pour les stress tests. */
    }
  else if (vars->hex_dump)
    hexdump(buffer, size);
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
  char prefix[128];
  int prefix_len;

  prefix_len = 0;
  if (vars->sequence_payload)
    {
      prefix_len = snprintf(prefix, sizeof(prefix), "SEQ:%d:%s:", vars->build_seq, vars->message);
      if (prefix_len < 0)
        prefix_len = 0;
      if ((size_t)prefix_len > sizeof(prefix))
        prefix_len = (int)sizeof(prefix);
    }

  if (vars->pcol == BP_TCP_FIXED_SIZE)
    {
      len = vars->payload_size > 0 ? vars->payload_size : DEFAULT_FIXED_SIZE;
      if ((size_t)len > buffer_size)
        len = (int)buffer_size;

      memset(buffer, 'A', (size_t)len);

      if (vars->sequence_payload && prefix_len > 0)
        {
          size_t plen = (size_t)prefix_len;
          if (plen > (size_t)len)
            plen = (size_t)len;
          memcpy(buffer, prefix, plen);
        }
      else if (vars->message[0] != '\0')
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

      if (vars->sequence_payload && prefix_len > 0)
        {
          size_t plen = (size_t)prefix_len;
          if (plen > (size_t)len)
            plen = (size_t)len;
          memcpy(buffer, prefix, plen);
        }
      else if (vars->message[0] != '\0')
        {
          size_t mlen = strlen(vars->message);
          if (mlen > (size_t)len)
            mlen = (size_t)len;
          memcpy(buffer, vars->message, mlen);
        }
      return len;
    }

  if (vars->sequence_payload)
    len = snprintf(buffer, buffer_size, "SEQ:%d:%s:sent at %lld\n",
                   vars->build_seq,
                   vars->message[0] != '\0' ? vars->message : "msg",
                   (long long)now_ms());
  else if (vars->message[0] != '\0')
    len = snprintf(buffer, buffer_size, "%s\n", vars->message);
  else
    len = snprintf(buffer, buffer_size, "sent at %lld\n", (long long)now_ms());

  if (len < 0)
    len = 0;
  if ((size_t)len > buffer_size)
    len = (int)buffer_size;
  return len;
}

static int send_to_known_peers(struct s_data *vars, const void *buffer, size_t len)
{
  int i;
  int ok;

  ok = 0;
  if (vars->nbr_clients > 0)
    {
      for (i = 0; i < vars->nbr_clients; ++i)
        {
          bool r;

          vars->send_attempts += 1;
          r = bunny_network_write(vars->clients[i].info, buffer, len);
          printf("[SEND] peer %d size=%zu -> %s\n", i, len, r ? "OK" : "FAIL");
          if (vars->verbose)
            print_info("  peer:", vars->clients[i].info);

          if (r)
            {
              ok += 1;
              vars->send_ok += 1;
              vars->sent_bytes += len;
              vars->clients[i].sent_ok += 1;
              vars->clients[i].sent_bytes += len;
            }
          else
            {
              vars->send_fail += 1;
              vars->clients[i].sent_fail += 1;
            }
        }
      return ok;
    }

  if (vars->has_remote && vars->net.socklen != 0)
    {
      bool r;

      vars->send_attempts += 1;
      r = bunny_network_write(vars->net, buffer, len);
      printf("[SEND] net size=%zu -> %s\n", len, r ? "OK" : "FAIL");
      if (vars->verbose)
        print_info("  net :", vars->net);

      if (r)
        {
          vars->send_ok += 1;
          vars->sent_bytes += len;
          return 1;
        }
      vars->send_fail += 1;
      return 0;
    }

  vars->send_skipped += 1;
  printf("[SEND] skipped no-peer\n");
  return 0;
}

static t_bunny_response loop_cb(void *data)
{
  struct s_data *vars = (struct s_data*)data;
  int64_t now;
  char buffer[4096];
  int len;
  int sent;

  now = now_ms();

  if (g_stop_requested)
    return EXIT_ON_SUCCESS;

  if (vars->duration_ms > 0 && now - vars->start_ms >= vars->duration_ms)
    return EXIT_ON_SUCCESS;

  if (vars->no_send)
    return GO_ON;

  if (vars->send_count > 0 && vars->sent_count >= vars->send_count)
    return GO_ON;

  if (now < vars->next_send_ms)
    return GO_ON;

  len = build_payload(vars, buffer, sizeof(buffer));
  sent = send_to_known_peers(vars, buffer, (size_t)len);

  if (sent > 0)
    {
      vars->sent_count += 1;
      vars->build_seq += 1;
    }
  vars->next_send_ms = now + vars->interval_ms;
  return GO_ON;
}

static void print_summary(struct s_data *vars)
{
  int i;
  int64_t now;

  now = now_ms();
  printf("[SUMMARY] proto=%s uptime_ms=%lld peers=%d no_send=%s duration_ms=%d first_send_delay_ms=%d quiet_payload=%s sequence_payload=%s loop_freq=%d sent_rounds=%d send_attempts=%d send_ok=%d send_fail=%d send_skipped=%d received_messages=%d sent_bytes=%zu received_bytes=%zu\n",
         proto_name(vars->pcol),
         (long long)(now - vars->start_ms),
         vars->nbr_clients,
         vars->no_send ? "yes" : "no",
         vars->duration_ms,
         vars->first_send_delay_ms,
         vars->quiet_payload ? "yes" : "no",
         vars->sequence_payload ? "yes" : "no",
         vars->loop_freq,
         vars->sent_count,
         vars->send_attempts,
         vars->send_ok,
         vars->send_fail,
         vars->send_skipped,
         vars->received_messages,
         vars->sent_bytes,
         vars->received_bytes);

  for (i = 0; i < vars->nbr_clients; ++i)
    {
      printf("[PEER] index=%d connected=%s age_ms=%lld idle_ms=%lld sent_ok=%d sent_fail=%d received_messages=%d sent_bytes=%zu received_bytes=%zu seq_seen=%s last_seq=%d seq_gaps=%d seq_duplicates=%d seq_regressions=%d\n",
             i,
             vars->clients[i].connected ? "yes" : "no",
             (long long)(now - vars->clients[i].first_seen_ms),
             (long long)(now - vars->clients[i].last_seen_ms),
             vars->clients[i].sent_ok,
             vars->clients[i].sent_fail,
             vars->clients[i].received_messages,
             vars->clients[i].sent_bytes,
             vars->clients[i].received_bytes,
             vars->clients[i].seq_seen ? "yes" : "no",
             vars->clients[i].last_seq,
             vars->clients[i].seq_gaps,
             vars->clients[i].seq_duplicates,
             vars->clients[i].seq_regressions);
      if (vars->verbose)
        print_info("  peer:", vars->clients[i].info);
    }
}

static int usage(const char *prog)
{
  fprintf(stderr,
          "Usage:\n"
          "  %s [-v] [--hex] [--quiet-payload] [--seq] [--no-send] [-D duration_ms] [--first-send-delay ms] [-F loop_freq] -p proto [-L port] [-R ip port] [-s size] [-n count] [-i ms] [-m text]\n"
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
  vars.loop_freq = DEFAULT_FREQ;
  vars.send_count = DEFAULT_COUNT;
  vars.payload_size = 0;
  vars.start_ms = now_ms();
  vars.next_send_ms = vars.start_ms + vars.interval_ms;

  signal(SIGTERM, handle_signal);
  signal(SIGINT, handle_signal);

  for (i = 1; i < argc; ++i)
    {
      if (strcmp(argv[i], "-v") == 0)
        vars.verbose = true;
      else if (strcmp(argv[i], "--hex") == 0)
        vars.hex_dump = true;
      else if (strcmp(argv[i], "--quiet-payload") == 0)
        vars.quiet_payload = true;
      else if (strcmp(argv[i], "--seq") == 0 || strcmp(argv[i], "--sequence") == 0)
        vars.sequence_payload = true;
      else if (strcmp(argv[i], "--no-send") == 0)
        vars.no_send = true;
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
      else if (strcmp(argv[i], "-F") == 0 || strcmp(argv[i], "--freq") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          vars.loop_freq = atoi(argv[++i]);
          if (vars.loop_freq <= 0)
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "-D") == 0 || strcmp(argv[i], "--duration") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          vars.duration_ms = atoi(argv[++i]);
          if (vars.duration_ms <= 0)
            return usage(argv[0]);
        }
      else if (strcmp(argv[i], "--first-send-delay") == 0)
        {
          if (i + 1 >= argc)
            return usage(argv[0]);
          vars.first_send_delay_ms = atoi(argv[++i]);
          if (vars.first_send_delay_ms < 0)
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
        return usage(argv[0]);
    }

  vars.next_send_ms = vars.start_ms + vars.interval_ms + vars.first_send_delay_ms;

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
    return usage(argv[0]);

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
      max = vars.payload_size > 0 ? vars.payload_size : DEFAULT_UDP_MAX;
      break;
    case BP_UDP_RELIABLE:
      max = vars.payload_size > 0 ? vars.payload_size : DEFAULT_RUDP_MAX;
      break;
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
  bunny_loop(NULL, vars.loop_freq, &vars);

  print_summary(&vars);
  bunny_network_close(vars.net);
  return 0;
}
