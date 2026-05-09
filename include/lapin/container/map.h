/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file map.h
** Binary map associating keys with raw data pointers.
**
** A map stores keys according to a comparison function. Optional duplication
** and deletion callbacks allow it to own keys. Stored data pointers remain the
** responsibility of the caller unless a helper explicitly frees them.
*/

#ifndef				__LAPIN_MAP_H__
# define			__LAPIN_MAP_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<string.h>

/**
 * @doc
 * @doc-symbol t_bunny_map_cmp
 * @doc-kind type
 * @doc-module map
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the comparison callback used to order map keys.
 * @param a The first key to compare.
 * @param b The second key to compare.
 * @param param The user pointer stored in the map.
 * @return-success Returns a negative, zero or positive value like $Sstrcmp@.
 * @see t_bunny_map, bunny_new_map
 *
 * @doc-lang fr
 * @brief Définit le callback de comparaison utilisé pour ordonner les clés de map.
 * @param a La première clé à comparer.
 * @param b La seconde clé à comparer.
 * @param param Le pointeur utilisateur stocké dans la map.
 * @return-success Renvoie une valeur négative, nulle ou positive comme $Sstrcmp@.
 * @see t_bunny_map, bunny_new_map
 */
typedef int			(*t_bunny_map_cmp)(const void		*a,
						   const void		*b,
						   void			*param);
/**
 * @doc
 * @doc-symbol t_bunny_map_dup
 * @doc-kind type
 * @doc-module map
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback used to duplicate map keys.
 * @param a The key to duplicate.
 * @param param The user pointer stored in the map.
 * @return-success Returns the duplicated key.
 * @see t_bunny_map, bunny_new_map
 *
 * @doc-lang fr
 * @brief Définit le callback utilisé pour dupliquer les clés de map.
 * @param a La clé à dupliquer.
 * @param param Le pointeur utilisateur stocké dans la map.
 * @return-success Renvoie la clé dupliquée.
 * @see t_bunny_map, bunny_new_map
 */
typedef void			*(*t_bunny_map_dup)(const void		*a,
						    void		*param);
/**
 * @doc
 * @doc-symbol t_bunny_map_del
 * @doc-kind type
 * @doc-module map
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback used to destroy map keys.
 * @param elem_to_free The key to release.
 * @param param The user pointer stored in the map.
 * @return-success This callback does not return a value.
 * @see t_bunny_map, bunny_new_map
 *
 * @doc-lang fr
 * @brief Définit le callback utilisé pour détruire les clés de map.
 * @param elem_to_free La clé à libérer.
 * @param param Le pointeur utilisateur stocké dans la map.
 * @return-success Ce callback ne renvoie pas de valeur.
 * @see t_bunny_map, bunny_new_map
 */
typedef void			(*t_bunny_map_del)(void			*elem_to_free,
						   void			*param);

/*!
** The handy structure to represent an element of your map, or
** the root of your tree or subtree.
*/
/**
 * @doc
 * @doc-symbol t_bunny_map
 * @doc-kind type
 * @doc-module map
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents one node or the root of a binary map.
 * @description The root stores callbacks while child nodes store key/data pairs. Stored data pointers remain owned by the caller.
 * @see bunny_new_map, bunny_map_set_data
 *
 * @doc-lang fr
 * @brief Représente un nœud ou la racine d'une map binaire.
 * @description La racine stocke les callbacks tandis que les nœuds enfants stockent les paires clé/donnée. Les pointeurs de données restent la propriété de l'appelant.
 * @see bunny_new_map, bunny_map_set_data
 */
typedef struct			s_bunny_map
{
  const void * const		data;
  const void * const		key;
  size_t			nbr_children;
  struct s_bunny_map * const	up;
  struct s_bunny_map * const	right;
  struct s_bunny_map * const	left;
  const t_bunny_map_cmp		cmp;
  const t_bunny_map_dup		dup;
  const t_bunny_map_del		del;
  const void * const		param;
}				t_bunny_map;

/*!
** Create a new map.
** \param cmp A function that will serve to sort and search into the map,
**            it must be able to compare two keys and return <0, 0 or 0< depending
**            of a < b, a == b and a > b. If cmp is NULL, the pointer stored are
**            compared. (Fitting behavior for a map of int type)
** \param dup This function can duplicate keys. It is useful to store
**            key inside the map. It can return NULL on error. The allocation
**            will be freed by the del function. Can be NULL if the type is
**            scalar.
** \param del Delete the sent key. Can be NULL if it does not need to be freed.
** \param param A parameter that will be sent to cmp, dup and del functions.
** \return Return null on failure, else a map
*/
t_bunny_map			*bunny_new_map(t_bunny_map_cmp		cmp,
					       t_bunny_map_dup		dup,
					       t_bunny_map_del		del,
					       void			*param);
/**
 * @doc
 * @doc-symbol string_map
 * @doc-kind variable
 * @doc-module map
 * @doc-order 185
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Expands to callbacks suitable for string-keyed maps.
 * @see bunny_new_map, bunny_string_map_get
 *
 * @doc-lang fr
 * @brief Se développe en callbacks adaptés aux maps indexées par chaînes.
 * @see bunny_new_map, bunny_string_map_get
 */
# define			string_map				\
  (t_bunny_map_cmp)strcmp, (t_bunny_map_dup)bunny_strdup, (t_bunny_map_del)bunny_free, NULL
/**
 * @doc
 * @doc-symbol int_map
 * @doc-kind variable
 * @doc-module map
 * @doc-order 190
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Expands to callbacks suitable for scalar or pointer keys.
 * @see bunny_new_map
 *
 * @doc-lang fr
 * @brief Se développe en callbacks adaptés aux clés scalaires ou pointeurs.
 * @see bunny_new_map
 */
# define			int_map					NULL, NULL, NULL, NULL

/*!
** Delete the map.
** \param list The list to destroy
** \return How many elements was in map
*/
size_t				bunny_delete_map(t_bunny_map		*map);

/*
**
*/
size_t				bunny_map_clear(t_bunny_map		*map);

/*!
** Get how many elements there is in the map.
** \param map The map to get the length
** \return The map size as size_t
*/
/**
 * @doc
 * @doc-symbol bunny_map_size
 * @doc-kind function
 * @doc-module map
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the number of entries stored in a map.
 * @param map The map to inspect.
 * @return-success Returns the map size.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Renvoie le nombre d'entrées stockées dans une map.
 * @param map La map à inspecter.
 * @return-success Renvoie la taille de la map.
 * @see t_bunny_map
 */
# define			bunny_map_size(map)			((map)->nbr_children)

/*!
** Test if the map is empty.
** \param map The map to test
** \return True if it is empty
*/
/**
 * @doc
 * @doc-symbol bunny_map_empty
 * @doc-kind function
 * @doc-module map
 * @doc-order 240
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests whether a map is empty.
 * @param map The map to inspect.
 * @return-success Returns $Ctrue@ if the map is empty.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Teste si une map est vide.
 * @param map La map à inspecter.
 * @return-success Renvoie $Ctrue@ si la map est vide.
 * @see t_bunny_map
 */
# define			bunny_map_empty(map)			(!(map)->nbr_children)

/*!
** Get the node that match the sent key.
** \param map The map to browse
** \param key The key to match
** \param create Create if it does not exists
** \return A node that match the sent key. May return NULL if create is false
**         and the tree does not contains a node matching key.
*/
t_bunny_map			*bunny_map_get_subtree(t_bunny_map	*map,
						       void		*key,
						       bool		create);

/*!
** Get the data inside the current map node with the correct type.
** \param node A t_bunny_map pointer
** \param type The type of the data that is contained by that map node.
** \return The data inside the map node with the correct type.
*/
/**
 * @doc
 * @doc-symbol bunny_map_data
 * @doc-kind function
 * @doc-module map
 * @doc-order 280
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads the data stored in a map node with the requested type.
 * @param map The map node to inspect.
 * @param typ The expected stored pointer type.
 * @return-success Returns the typed data pointer stored in the node.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Lit la donnée stockée dans un nœud de map avec le type demandé.
 * @param map Le nœud de map à inspecter.
 * @param typ Le type attendu du pointeur stocké.
 * @return-success Renvoie le pointeur de donnée typé stocké dans le nœud.
 * @see t_bunny_map
 */
# define			bunny_map_data(map, typ)		((typ)(size_t)(map)->data)

/*!
** Get the data that match the sent key.
** \param map The map to browse
** \param key The key to match
** \return The data, or NULL if it does not exists
*/
void				*_bunny_map_get_data(t_bunny_map	*map,
						     void		*key);

/*!
** Get the data that match the sent key.
** \param map The map to browse
** \param key The key to match
** \param type The type of the data that is contained by the node
** \return The data, or NULL if it does not exists
*/
/**
 * @doc
 * @doc-symbol bunny_map_get_data
 * @doc-kind function
 * @doc-module map
 * @doc-order 300
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the data associated with a key.
 * @param map The map to browse.
 * @param key The key to search.
 * @param type The expected returned pointer type.
 * @return-success Returns the typed data pointer, or $CNULL@ if the key is missing.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Renvoie la donnée associée à une clé.
 * @param map La map à parcourir.
 * @param key La clé à chercher.
 * @param type Le type attendu du pointeur renvoyé.
 * @return-success Renvoie le pointeur de donnée typé, ou $CNULL@ si la clé est absente.
 * @see t_bunny_map
 */
# define			bunny_map_get_data(map, key, type)	\
  (type)(size_t)_bunny_map_get_data(map,(void*)(size_t)key)

/*!
** Set a data inside the map that match the sent key. It creates nodes
** if required.
** \param map The map to edit
** \param key The key to match
** \param data The data to store
** \return The previous data that was stored in the matching node, or
**         the new one if there was no previous value (or it was NULL).
**         Or NULL on error.
*/
void				*_bunny_map_set_data(t_bunny_map	*map,
						     void		*key,
						     void		*data);

/*!
** Set a data inside the map that match the sent key. It creates nodes
** if required.
** \param map The map to edit
** \param k The key to match
** \param da The data to store
** \param typ The type of the returned data.
** \return The previous data that was stored in the matching node, or
**         the new one if there was no previous value (or it was NULL).
**         Or NULL on error.
*/
/**
 * @doc
 * @doc-symbol bunny_map_set_data
 * @doc-kind function
 * @doc-module map
 * @doc-order 320
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Associates data with a key in a map.
 * @param map The map to edit.
 * @param k The key to associate.
 * @param d The data pointer to store.
 * @param typ The expected returned pointer type.
 * @return-success Returns the previous data pointer, or the new one when there was no previous value.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Associe une donnée à une clé dans une map.
 * @param map La map à modifier.
 * @param k La clé à associer.
 * @param d Le pointeur de donnée à stocker.
 * @param typ Le type attendu du pointeur renvoyé.
 * @return-success Renvoie le pointeur précédent, ou le nouveau lorsqu'il n'y avait pas de valeur précédente.
 * @see t_bunny_map
 */
# define			bunny_map_set_data(map, k, d, typ)	\
  ((typ)_bunny_map_set_data(map, (void*)(size_t)k, (void*)(size_t)d))

/*!
** Call the func function on every data of the sent map.
** \param map The map to edit
** \param func The func to apply
** \param param The second parameter sent to func
*/
void				bunny_map_foreach(t_bunny_map		*map,
						  void			(*func)
						  (t_bunny_map		*node,
						   void			*param),
						  void			*param);

/*!
** Call the func function on every data of the sent map with multiple threads
** \param pool The thread pool that will share its threads
** \param map The map to edit
** \param func The func to apply
** \param param The second parameter sent to func
** \return False to notice you an error happened with threads: all datas
**         were not treated by threads, some of them were treated by the
**         main thread because of thread pool memory exhaustion.
**         True if all was ok.
**
** You should use bunny_thread_wait_completion at the end of your thread cycle.
*/
bool				bunny_map_fast_foreach(t_bunny_threadpool *pool,
						       t_bunny_map	*map,
						       void		(*func)
						       (t_bunny_map	*map,
							void		*param),
						       void		*param);

t_bunny_map			**_bunny_map_begin(t_bunny_map		*map,
						   void			*buf);

/**
 * @doc
 * @doc-symbol bunny_map_begin
 * @doc-kind function
 * @doc-module map
 * @doc-order 380
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a temporary iterator array over all map nodes.
 * @param map The map to browse.
 * @return-success Returns the first cell of a $CNULL@-terminated array of node pointers.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Crée un tableau temporaire d'itération sur tous les nœuds d'une map.
 * @param map La map à parcourir.
 * @return-success Renvoie la première case d'un tableau de pointeurs de nœuds terminé par $CNULL@.
 * @see t_bunny_map
 */
# define			bunny_map_begin(map)			\
  _bunny_map_begin((map), bunny_alloca(sizeof(*(map)) * (bunny_map_size(map) + 1)))
/**
 * @doc
 * @doc-symbol bunny_map_end
 * @doc-kind function
 * @doc-module map
 * @doc-order 400
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the map iterator sentinel.
 * @param map Ignored argument kept for loop symmetry.
 * @return-success Returns $CNULL@.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Renvoie la sentinelle d'itérateur de map.
 * @param map Argument ignoré conservé pour la symétrie des boucles.
 * @return-success Renvoie $CNULL@.
 * @see t_bunny_map
 */
# define			bunny_map_end(map)			\
  NULL
/**
 * @doc
 * @doc-symbol bunny_map_next
 * @doc-kind function
 * @doc-module map
 * @doc-order 420
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Advances a map iterator.
 * @param nod The current iterator cell.
 * @return-success Returns the next iterator cell.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Avance un itérateur de map.
 * @param nod La case d'itération courante.
 * @return-success Renvoie la case d'itération suivante.
 * @see t_bunny_map
 */
# define			bunny_map_next(nod)			\
  (nod) + 1

/**
 * @doc
 * @doc-symbol bunny_map_all
 * @doc-kind function
 * @doc-module map
 * @doc-order 440
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Builds a for-loop clause that browses all map nodes.
 * @param map The map to browse.
 * @param nod The iterator variable.
 * @return-success This macro expands to the expressions of a $Kfor@ loop.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Construit une clause de boucle for parcourant tous les nœuds d'une map.
 * @param map La map à parcourir.
 * @param nod La variable d'itération.
 * @return-success Cette macro se développe en expressions de boucle $Kfor@.
 * @see t_bunny_map
 */
# define			bunny_map_all(map, nod)			\
  nod = bunny_map_begin(map); *nod != bunny_map_end(nod); nod = bunny_map_next(nod)

const char			*bunny_string_map_get(t_bunny_map	*map,
						      const char	*key);
const char			*bunny_string_map_set(t_bunny_map	*map,
						      const char	*key,
						      const char	*val);
/**
 * @doc
 * @doc-symbol bunny_string_map_clear
 * @doc-kind function
 * @doc-module map
 * @doc-order 500
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Clears the string value associated with a key.
 * @param map The string map to edit.
 * @param key The key to clear.
 * @return-success Returns the result of $Sbunny_string_map_set@.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Vide la valeur chaîne associée à une clé.
 * @param map La string map à modifier.
 * @param key La clé à vider.
 * @return-success Renvoie le résultat de $Sbunny_string_map_set@.
 * @see t_bunny_map
 */
# define			bunny_string_map_clear(map, key)	\
  bunny_string_map_set(map, key, NULL)
/**
 * @doc
 * @doc-symbol bunny_delete_string_map
 * @doc-kind function
 * @doc-module map
 * @doc-order 520
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a string map and every duplicated string value.
 * @param map The string map to delete.
 * @return-success This macro does not return a value.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Détruit une string map et chaque valeur chaîne dupliquée.
 * @param map La string map à détruire.
 * @return-success Cette macro ne renvoie pas de valeur.
 * @see t_bunny_map
 */
# define			bunny_delete_string_map(map)		\
  do {									\
    if (map)								\
      {									\
	for (t_bunny_map **nod = bunny_map_begin(map);			\
	     *nod != bunny_map_end(nod);				\
	     nod = bunny_map_next(nod)) {				\
	  bunny_free(bunny_map_data(*nod, char*));			\
	}								\
	bunny_delete_map(map);						\
      }									\
  } while (0)
/**
 * @doc
 * @doc-symbol bunny_print_string_map
 * @doc-kind function
 * @doc-module map
 * @doc-order 540
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Prints all pairs of a string map.
 * @param map The string map to print.
 * @param fd The file descriptor where text is written.
 * @param cnt A counter incremented by the number of written characters.
 * @return-success This macro updates $Scnt@.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Affiche toutes les paires d'une string map.
 * @param map La string map à afficher.
 * @param fd Le descripteur de fichier où écrire le texte.
 * @param cnt Un compteur incrémenté du nombre de caractères écrits.
 * @return-success Cette macro met à jour $Scnt@.
 * @see t_bunny_map
 */
# define			bunny_print_string_map(map, fd, cnt)	\
  do {									\
    if (map)								\
      for (t_bunny_map **nod = bunny_map_begin(map);			\
	   *nod != bunny_map_end(nod);					\
	   nod = bunny_map_next(nod)) {					\
	cnt += bunny_dprintf(fd, "%s: %s\n", (*nod)->key, (*nod)->data); \
      }									\
  } while (0)

#endif	/*			__LAPIN_MAP_H__				*/

