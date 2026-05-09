/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

/*!
** \file container.h
** Generic containers used by the bunny library.
**
** This module gathers small C containers: stack, automatic stack, queue, list,
** map, vector, pool and bitfield. Most containers store user data as raw
** pointers. The containers own their internal nodes, but they generally do not
** own the pointed data unless explicitly documented by a helper.
*/

#ifndef				__LAPIN_CONTAINER_H__
# define			__LAPIN_CONTAINER_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdarg.h>

/*!
** Function called by managed containers to initialize an element.
**
** \param data The element storage to initialize.
** \param add User parameter forwarded by the container creation/resizing call.
** \return True on success, false on construction failure.
*/
/**
 * @doc
 * @doc-symbol t_bunny_constructor
 * @doc-kind type
 * @doc-module container
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the constructor callback used by managed containers.
 * @param data The element storage to initialize.
 * @param add The user pointer forwarded by the container.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on construction failure.
 * @see t_bunny_destructor, t_bunny_vector, t_bunny_pool
 *
 * @doc-lang fr
 * @brief Définit le callback constructeur utilisé par les conteneurs gérés.
 * @param data Le stockage de l'élément à initialiser.
 * @param add Le pointeur utilisateur transmis par le conteneur.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d'échec de construction.
 * @see t_bunny_destructor, t_bunny_vector, t_bunny_pool
 */
typedef bool			(*t_bunny_constructor)(void		*data,
						       void		*add);
/*!
** Function called by managed containers to destroy an element.
**
** \param data The element storage to destroy.
** \return True on success, false on destruction failure.
*/
/**
 * @doc
 * @doc-symbol t_bunny_destructor
 * @doc-kind type
 * @doc-module container
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the destructor callback used by managed containers.
 * @param data The element storage to destroy.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on destruction failure.
 * @see t_bunny_constructor, t_bunny_vector
 *
 * @doc-lang fr
 * @brief Définit le callback destructeur utilisé par les conteneurs gérés.
 * @param data Le stockage de l'élément à détruire.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d'échec de destruction.
 * @see t_bunny_constructor, t_bunny_vector
 */
typedef bool			(*t_bunny_destructor)(void		*data);

# include			"container/stack.h"
# include			"container/astack.h"
# include			"container/queue.h"
# include			"container/list.h"
# include			"container/map.h"
# include			"container/vector.h"
# include			"container/pool.h"
# include			"container/bitfield.h"

/*!
** Helper callback for bunny_map_foreach that frees each node data with bunny_free.
**
** \param nod The current map node.
** \param d Unused user parameter.
*/
void				bunny_foreach_map_bunny_free(t_bunny_map *nod,
							     void	*d);

#endif	/*			__LAPIN_CONTAINER_H__			*/
