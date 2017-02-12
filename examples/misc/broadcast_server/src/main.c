/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** BroadCast server
*/

#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>
#include		<stdlib.h>

t_bunny_server		*srv;

#define			NEWCLIENT		-1
#define			DEADCLIENT		-2
#define			TOO_MANY_CLIENT		-3

void			bye(int			i)
{
  (void)i;
  bunny_delete_server(srv);
  puts("Good bye.");
  exit(EXIT_SUCCESS);
}

int			main(int		argc,
			     char		**argv)
{
  const t_bunny_communication	*com;
  int			fd_tab[1024];
  int			i;

  assert(argc == 2);
  for (i = 0; i < 1024; ++i)
    fd_tab[i] = -1;
  if ((srv = bunny_new_server(atoi(argv[1]))) == NULL)
    return (EXIT_FAILURE);
  puts("Started.");
  do
    {
      com = bunny_server_poll(srv, 1);
      switch (com->comtype)
	{
	case ERROR:
	  break ;
	case NETCONNECTED:
	  fprintf(stdout, "New client %d.\n", com->connected.fd);
	  if (com->connected.fd >= 1024)
	    bunny_server_doom_client(srv, com->connected.fd);
	  else
	    fd_tab[com->connected.fd] = com->connected.fd;
	  break ;
	case NETDISCONNECTED:
	  fprintf(stdout, "Dead client %d.\n", com->disconnected.fd);
	  fd_tab[com->disconnected.fd] = -1;
	  break ;
	case MESSAGE:
	  fprintf(stdout, "Broadcasting for %d. Size is %u\n", com->message.fd, com->message.size);
	  for (i = 0; i < 1024; ++i)
	    if (fd_tab[i] != -1 && fd_tab[i] != com->message.fd)
	      {
		fprintf(stdout, "Sent to %d.\n", fd_tab[i]);
		if (bunny_server_write(srv, com->message.buffer, com->message.size, fd_tab[i]) == false)
		  fprintf(stderr, "Failed to write a message.\n");
	      }
	default:
	  break ;
	}
    }
  while (1);
  return (0);
}

