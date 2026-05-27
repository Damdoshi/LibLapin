// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin.h"


/**
 * @doc
 * @doc-symbol bunny_infocmp
 * @doc-kind function
 * @doc-module network
 * @doc-order 40
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Compares two network endpoint identifiers.
 * @param a First endpoint.
 * @param b Second endpoint.
 * @return-success Returns a negative, zero or positive value depending on the ordering of a and b.
 * @see t_bunny_network_info, bunny_new_network_info
 *
 * @doc-lang fr
 * @brief Compare deux identifiants d'extrémité réseau.
 * @param a Première extrémité.
 * @param b Seconde extrémité.
 * @return-success Renvoie une valeur négative, nulle ou positive selon l'ordre de a et b.
 * @see t_bunny_network_info, bunny_new_network_info
 */
static int		cmp_uint(unsigned int	a,
				 unsigned int	b)
{
  return ((a > b) - (a < b));
}

int			bunny_infocmp(t_bunny_network_info	a,
				      t_bunny_network_info	b)
{
  int			diff;

  if (!a.socklen || !b.socklen)
    return (cmp_uint(a.socklen, b.socklen));
  if ((diff = cmp_uint(a.sockaddr.sin_family, b.sockaddr.sin_family)) != 0)
    return (diff);
  if ((diff = cmp_uint(a.sockaddr.sin_addr.s_addr, b.sockaddr.sin_addr.s_addr)) != 0)
    return (diff);
  return (cmp_uint(a.sockaddr.sin_port, b.sockaddr.sin_port));
}
