// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_resolve_identity
 * @doc-kind function
 * @doc-module network
 * @doc-order 540
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Finds an identity entry matching a network endpoint.
 * @param id Identity array to search.
 * @param in Endpoint to resolve.
 * @return-success Returns the matching identity entry.
 * @return-failure Returns NULL if no entry matches.
 * @see t_bunny_identity, gl_bunny_identity
 *
 * @doc-lang fr
 * @brief Trouve une entrée d'identité correspondant à une extrémité réseau.
 * @param id Tableau d'identités à parcourir.
 * @param in Extrémité à résoudre.
 * @return-success Renvoie l'entrée d'identité correspondante.
 * @return-failure Renvoie NULL si aucune entrée ne correspond.
 * @see t_bunny_identity, gl_bunny_identity
 */
t_bunny_identity	*bunny_resolve_identity(t_bunny_identity	*id,
						t_bunny_network_info	in)
{
  for (size_t i = 0; id[i].identity[0]; ++i)
    if (bunny_infocmp(id[i].info, in) == 0)
      return (&id[i]);
  return (NULL);
}

