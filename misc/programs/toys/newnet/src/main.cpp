#include	"lapin.h"

struct s_data {
  t_bunny_network_info		net;
  t_bunny_network_info		clients[1024];
  int				nbr_clients;
  time_t			start;
  t_bunny_protocol		pcol;
  bool				is_server;
  bool				verbose;
};

static t_bunny_response connect(t_bunny_network_info		info,
				t_bunny_event_state		state,
				void				*data)
{
  s_data		*vars = (s_data*) data;
  if (state == DISCONNECTED)
    {
      if (!vars->nbr_clients)
	return (EXIT_ON_SUCCESS);
      int i = 0;

      while (i < vars->nbr_clients && !memcmp(&vars->clients[i], &info, sizeof(info)))
	i = i + 1;
      printf("User %d disconnected. User %d will now be user %d.\n", i, vars->nbr_clients - 1, i);
      vars->clients[i] = vars->clients[vars->nbr_clients - 1];
      vars->nbr_clients -= 1;
      return (GO_ON);
    }
  vars->clients[vars->nbr_clients] = info;
  printf("New user, user %d\n", vars->nbr_clients);
  vars->nbr_clients += 1;
  // for (int i = 0; i < vars->nbr_clients; ++i)
  // printf("Client %d %p\n", i, &vars->clients[i]);
  return (GO_ON);
}

static t_bunny_response message(t_bunny_network_info		info,
				void				*buffer,
				size_t				size,
				void				*data)
{
  s_data		*vars = (s_data*) data;
  int			i = 0;

  while (i < vars->nbr_clients && !memcmp(&vars->clients[i], &info, sizeof(info)))
    i = i + 1;
  printf("Message received from %d: ", i);
  fflush(stdout);
  write(1, buffer, size);
  write(1, "\n", 1);
  bunny_free(buffer);
  return (GO_ON);
}

static t_bunny_response loop(void				*data)
{
  static int		cnt = 0;
  char			buffer[128];
  time_t		now = time(NULL);
  int			len;
  s_data		*vars = (s_data *) data;

  if (cnt % 10 == 0)
    {
      if (vars->verbose)
	bunny_network_dump(2);
      vars->start = now;
      len = snprintf(buffer, sizeof(buffer), "sent at %ld\n", now);
      // Si on est un serveur TCP
      if (vars->nbr_clients != 0)
	{
	  for (int i = 0; i < vars->nbr_clients; ++i)
	    if (bunny_network_write(vars->clients[i], buffer, len) == false)
	      fprintf(stderr, "failed to write '%s' to nbr %d\n", buffer, i);
	}
      // Sinon
      else if (!vars->is_server)
	if (bunny_network_write(vars->net, buffer, len) == false)
	  fprintf(stderr, "failed to write '%s'\n", buffer);
    }
  cnt += 1;
  return (GO_ON);
}

static int	usage(void)
{
  printf(
	 "Usage is:\n"
	 "  ./prog ([-l port] | [ip port]) [-p protocol]\n\n"
	 "  Protocols are:\n\n"
	 "\t- udp (default)\n"
	 "\t- tcp - no packet shape. an optional maximum size can be given, default is 1Mo\n"
	 "\t- rudp [udp] - an optional timeout and resend can be specified\n"
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
  char		*ip = NULL;
  int		port = 0;
  int		max = 0;
  static s_data	vars;

  memset(&vars, 0, sizeof(vars));
  if (argc == 1)
    return (usage());
  for (int i = 1; i < argc; ++i)
    {
      if (strcmp("-v", argv[i]) == 0)
	vars.verbose = true;
      else if (strcmp("-l", argv[i]) == 0)
	{
	  if ((i += 1) >= argc)
	    return (usage());
	  vars.is_server = true;
	  if ((port = atoi(argv[i])) <= 0 || port > 65535)
	    return (usage());
	}
      else if (strcmp("-p", argv[i]) == 0)
	{
	  if ((i += 1) >= argc)
	    return (usage());
	  if (strcasecmp(argv[i], "udp") == 0)
	    vars.pcol = BP_UDP_IMMEDIATE;
	  else if (strcasecmp(argv[i], "tcp") == 0)
	    {
	      vars.pcol = BP_TCP_IMMEDIATE;
	      max = 1024 * 1024;
	      if (i + 1 < argc)
		{
		  i += 1;
		  if ((max = atoi(argv[i])) <= 0)
		    return (usage());
		}
	    }
	  else if (strcasecmp(argv[i], "rudp") == 0)
	    vars.pcol = BP_UDP_RELIABLE;
	  else if (strcasecmp(argv[i], "fixed") == 0)
	    {
	      vars.pcol = BP_TCP_FIXED_SIZE;
	      max = 64;
	      if (i + 1 < argc)
		{
		  i += 1;
		  if ((max = atoi(argv[i])) <= 0)
		    return (usage());
		}
	    }
	  else if (strcasecmp(argv[i], "size") == 0)
	    {
	      vars.pcol = BP_TCP_SIZED_PLUS_DATA;
	      max = 1024 * 1024;
	      if (i + 1 < argc)
		{
		  i += 1;
		  if ((max = atoi(argv[i])) <= 0)
		    return (usage());
		}
	    }
	  else if (strcasecmp(argv[i], "term") == 0)
	    {
	      vars.pcol = BP_TCP_TERMINATED_DATA;
	      max = 1460;
	      if (i + 1 < argc)
		{
		  i += 1;
		  if ((max = atoi(argv[i])) <= 0)
		    return (usage());
		}
	    }
	  else
	    return (usage());
	}
      else if (ip == NULL)
	{
	  if (vars.is_server)
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

  // Pas de notion de serveur en UDP
  if (vars.is_server && (vars.pcol == BP_UDP_IMMEDIATE || vars.pcol == BP_UDP_RELIABLE))
    vars.is_server = false;

  vars.net = bunny_network_open(vars.pcol,  max, '\v', 200, true, port, ip);
  if (vars.net.socklen == 0)
    {
      printf("Failed to open connexion.\n");
      return (1);
    }

  vars.start = time(NULL);
  bunny_set_loop_main_function(loop);
  bunny_set_connect_response(connect);
  bunny_set_message_response(message);
  bunny_loop(NULL, 10, &vars);

  bunny_network_close(vars.net);
  printf("Bye.\n");
  return (0);
}
