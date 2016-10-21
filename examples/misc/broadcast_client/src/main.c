/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<fcntl.h>
#include		<signal.h>
#include		<stdio.h>
#include		<lapin.h>

t_bunny_client		*clt;
int			flags;

void			bye(int                 i)
{
  (void)i;
  bunny_delete_client(clt);
  fcntl(0, F_SETFL, flags);
  exit(EXIT_SUCCESS);
}

int			main(int                argc,
			     char               **argv)
{
  const t_bunny_communication	*com;
  char			buffer[4096];
  int			i;

  if (argc != 3)
    return (EXIT_FAILURE);
  signal(SIGINT, bye);
  clt = bunny_new_client(argv[1], atoi(argv[2]));
  flags = fcntl(0, F_GETFL, 0);
  fcntl(0, F_SETFL, flags | O_NONBLOCK);
  do
    {
      com = bunny_client_poll(clt, 10);
      switch (com->comtype)
	{
	case ERROR:
	  bunny_delete_client(clt);
	  fprintf(stderr, "Client dies.\n");
	  fcntl(0, F_SETFL, flags);
	  return (EXIT_FAILURE);
	case NETDISCONNECTED:
	  bunny_delete_client(clt);
	  fprintf(stderr, "Server dies.\n");
	  fcntl(0, F_SETFL, flags);
	  return (EXIT_FAILURE);	    
	case MESSAGE:
	  write(1, com->message.buffer, com->message.size);
	default:
	  break ;
	}
      if ((i = read(0, &buffer[0], sizeof(buffer))) > 0)
	bunny_client_write(clt, &buffer[0], i);
      if (i == 0)
	{
	  bunny_delete_client(clt);
	  return (EXIT_FAILURE);
	}
    }
  while (1);
  return (0);
}




