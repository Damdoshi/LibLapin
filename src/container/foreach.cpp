// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

/*!
** Free the data stored in a map node.
**
** This helper is meant to be passed to bunny_map_foreach when the map stores
** heap allocated values that must be released with bunny_free.
**
** \param nod The current map node.
** \param d Unused user parameter.
*/
/**
 * @doc
 * @doc-symbol bunny_foreach_map_bunny_free
 * @doc-kind function
 * @doc-module container
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Frees the data pointer stored in a map node.
 * @param nod The current map node.
 * @param d Unused user parameter.
 * @see bunny_map_foreach, bunny_free
 *
 * @doc-lang fr
 * @brief Libère le pointeur de donnée stocké dans un nœud de map.
 * @param nod Le nœud de map courant.
 * @param d Paramètre utilisateur inutilisé.
 * @see bunny_map_foreach, bunny_free
 */
void			bunny_foreach_map_bunny_free(t_bunny_map *nod,
						     void	*d)
{
  (void)d;
  bunny_free(bunny_map_data(nod, void*));
}

