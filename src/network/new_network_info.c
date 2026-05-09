// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin.h"


/**
 * @doc
 * @doc-symbol bunny_new_network_info
 * @doc-kind function
 * @doc-module network
 * @doc-order 50
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Builds a t_bunny_network_info from an IPv4 string and port.
 * @param ip IPv4 address string, or NULL for any address.
 * @param port TCP or UDP port.
 * @return-success Returns the initialized endpoint descriptor.
 * @see t_bunny_network_info, bunny_network_open
 *
 * @doc-lang fr
 * @brief Construit un t_bunny_network_info depuis une chaîne IPv4 et un port.
 * @param ip Chaîne d'adresse IPv4, ou NULL pour n'importe quelle adresse.
 * @param port Port TCP ou UDP.
 * @return-success Renvoie le descripteur d'extrémité initialisé.
 * @see t_bunny_network_info, bunny_network_open
 */
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

