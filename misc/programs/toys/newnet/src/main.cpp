
#include	"lapin.h"

const t_bunny_network_info *net;
const t_bunny_network_info *clients[1024];
int nbr_clients;
time_t start;

static t_bunny_response connect(const t_bunny_network_info	*info,
				t_bunny_event_state		state,
				void *)
{
  if (state == DISCONNECTED)
    {
      int i = 0;

      while (i < nbr_clients && clients[i] != info)
	i = i + 1;
      printf("User %d disconnected.\n", i);
      printf("User %d will now be user %d.\n", nbr_clients - 1, i);
      clients[i] = clients[nbr_clients - 1];
      nbr_clients -= 1;
      return (GO_ON);
    }
  clients[nbr_clients] = info;
  printf("New user, user %d\n", nbr_clients);
  nbr_clients += 1;
  return (GO_ON);
}

static t_bunny_response message(const t_bunny_network_info	*info,
				const void			*buffer,
				size_t				size,
				void *)
{
  puts("I received something !");
  int i = 0;

  while (i < nbr_clients && clients[i] != info)
    i = i + 1;
  printf("Message received from %d: ", i);
  fflush(stdout);
  write(1, buffer, size);
  write(1, "\n", 1);
  return (GO_ON);
}

static t_bunny_response loop(void*)
{
  char buffer[128];
  time_t now = time(NULL);
  int len;

  puts("loop\n");
  if (now - start < 2)
    return (GO_ON);
  start = now;
  len = snprintf(buffer, sizeof(buffer), "sent at %ld\n", now);
  printf("Nbr clients : %d\n", nbr_clients);
  if (nbr_clients != 0)
    {
      for (int i = 0; i < nbr_clients; ++i)
	if (bunny_network_write(clients[i], buffer, len) == false)
	  fprintf(stderr, "failed to write '%s' to nbr %d\n", buffer, i);
    }
  else if (bunny_network_write(net, buffer, len) == false)
    fprintf(stderr, "failed to write '%s'\n", buffer);
  return (GO_ON);
}

static int	usage(void)
{
  printf(
	 "Usage is:\n"
	 "  ./prog ([-l port] | [ip port]) [-p protocol]\n\n"
	 "  Protocols are:\n\n"
	 "\t- udp (default)\n"
	 "\t- fixed [tcp] - an optional defined size can be given, default is 1460\n"
	 "\t- size [tcp] - an optional maximum size can be given, default is 1Mo\n"
	 "\t- term [tcp] - an optional maximum size can be given, default is 1460\n"
	 "\n"
	 );
  return (1);
}

int		main(int	argc,
		     char	**argv)
{
  t_bunny_protocol pcol = BP_IMMEDIATE_RETRIEVE;
  bool		listen = false;
  char		*ip = NULL;
  int		port = 0;
  int		max = 0;

  if (argc == 1)
    return (usage());
  for (int i = 1; i < argc; ++i)
    {
      if (strcmp("-l", argv[i]) == 0)
	{
	  if ((i += 1) >= argc)
	    return (usage());
	  listen = true;
	  if ((port = atoi(argv[i])) <= 0 || port > 65535)
	    return (usage());
	}
      else if (strcmp("-p", argv[i]) == 0)
	{
	  if ((i += 1) >= argc)
	    return (usage());
	  if (strcasecmp(argv[i], "udp") == 0)
	    pcol = BP_IMMEDIATE_RETRIEVE;
	  else if (strcasecmp(argv[i], "fixed") == 0)
	    {
	      pcol = BP_FIXED_SIZE_PACKET;
	      max = 1460;
	      if (i + 1 < argc)
		if ((max = atoi(argv[i])) <= 0)
		  return (usage());
	    }
	  else if (strcasecmp(argv[i], "size") == 0)
	    {
	      pcol = BP_SIZE_PLUS_DATA_PACKET;
	      max = 1024 * 1024;
	      if (i + 1 < argc)
		if ((max = atoi(argv[i])) <= 0)
		  return (usage());
	    }
	  else if (strcasecmp(argv[i], "term") == 0)
	    {
	      pcol = BP_TERMINATED_PACKET;
	      max = 1460;
	      if (i + 1 < argc)
		if ((max = atoi(argv[i])) <= 0)
		  return (usage());
	    }
	  else
	    return (usage());
	}
      else if (ip == NULL)
	{
	  if (listen)
	    return (usage());
	  ip = argv[i];
	}
      else if (port == 0)
	{
	  if ((port = atoi(argv[i])) <= 0 || port > 65535)
	    return (usage());
	}
      else
	return (usage());
    }

  puts("wesh");
  
  if ((net = bunny_network_open(pcol,  max, '\v', port, ip)) == NULL)
    {
      printf("Failed to open connexion.\n");
      return (1);
    }

  start = time(NULL);
  bunny_set_loop_main_function(loop);
  bunny_set_connect_response(connect);
  bunny_set_message_response(message);
  bunny_loop(NULL, 100, NULL);

  bunny_network_close(net);
  printf("Bye.\n");
  return (0);
}

