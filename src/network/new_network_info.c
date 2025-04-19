// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin.h"

t_bunny_network_info	bunny_new_network_info(const char	*ip,
					       uint16_t		port)
{
  t_bunny_network_info	inf;

  inf.sockaddr.sin_family = AF_INET;
  if (ip != NULL && *ip != 0)
    inf.sockaddr.sin_addr.s_addr = inet_addr(ip);
  else
    inf.sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  inf.sockaddr.sin_port = htons(port);
  inf.socklen = sizeof(inf.sockaddr);
  return (inf);
}

