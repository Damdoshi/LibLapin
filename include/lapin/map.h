/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file map.h
**
**
**
*/

#ifndef				__LAPIN_MAP_H__
# define			__LAPIN_MAP_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

typedef int			(*t_bunny_map_cmp)(const void		*a,
						   const void		*b,
						   void			*param);
typedef void			*(*t_bunny_map_dup)(const void		*a,
						    void		*param);
typedef void			(*t_bunny_map_del)(void			*elem_to_free,
						   void			*param);

/*!
** The handy structure to represent an element of your map, or
** the root of your tree or subtree.
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

/*!
** Delete the map.
** \param list The list to destroy
** \return How many elements was in map
*/
size_t				bunny_delete_map(t_bunny_map		*map);

/*!
** Get how many elements there is in the map.
** \param map The map to get the length
** \return The map size as size_t
*/
# define			bunny_map_size(map)			((map)->nbr_children)

/*!
** Test if the map is empty.
** \param map The map to test
** \return True if it is empty
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
# define			bunny_map_data(map, typ)		((typ)(map)->data)

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
# define			bunny_map_get_data(map, key, type)	\
  (type)_bunny_map_get_data(map,(void*)(size_t)key)

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
# define			bunny_map_set_data(map, k, d, typ)	\
  (typ)_bunny_map_set_data(map, (void*)(size_t)k, (void*)(size_t)d)

/*!
** Call the func function on every data of the sent map.
** \param map The map to edit
** \param func The func to apply
** \param param The second parameter sent to func
*/
void				bunny_map_foreach(t_bunny_map		*map,
						  void			(*func)
						  (void			*nod,
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
						       (void		*nod,
							const void	*param),
						       const void	*param);

#endif	/*			__LAPIN_MAP_H__				*/

