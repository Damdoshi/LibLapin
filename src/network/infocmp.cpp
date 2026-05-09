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
int			bunny_infocmp(t_bunny_network_info	a,
				      t_bunny_network_info	b)
{
  socklen_t		i;
  int			diff;

  i = 0;
  while (i < a.socklen && i < sizeof(a.sockaddr) &&
	 i < b.socklen && i < sizeof(b.sockaddr))
    if ((diff = ((char*)&a.sockaddr)[i] - ((char*)&b.sockaddr)[i]) != 0)
      return (diff);
    else
      i = i + 1;
  if ((i == a.socklen || i == sizeof(a.sockaddr)) &&
      (i == b.socklen || i == sizeof(b.sockaddr)))
    return (0);
  return (((char*)&a.sockaddr)[i] - ((char*)&b.sockaddr)[i]);
}
