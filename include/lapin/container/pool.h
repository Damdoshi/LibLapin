/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file pool.h
** A pool is useful if you need a fast container.
** Pay attention while using it, it is really more complex to use than it appeirs,
** if you try to build not foreach-like applications.
**
** Limitations are: only simple browsing is possible and size must
** be knowned at the beginning.
** Advantages:
**   complexity of allocation is 1
**   complexity of release is 1
**   full browsing complexity is N
**
** Pretty useful for video game bullet/monster pools, for example.
*/

#ifndef				__LAPIN_POOL_H__
# define			__LAPIN_POOL_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

typedef struct			s_bunny_pool
{
  const size_t			nmemb;
  const size_t			elemsize;
  const size_t			nbr_occupied;
  void * const			data[__ZERO_LENGTH__];
}				t_bunny_pool;

/*!
** Create a managed array of maximum nmemb elements of size size.
** \param nmemb How many elements there is in your pool
** \param size What is the size of a single element
** \return A pool or NULL on error
*/
t_bunny_pool			*_bunny_new_pool(size_t			nmemb,
						 size_t			size);

/*!
** Create a managed array of maximum nmemb elements of type typ
** \param nbr How many elements there is in your pool
** \param typ What is the type of elements inside your pool
** \return A pool or NULL on error
*/
# define			bunny_new_pool(nbr, typ)		\
  _bunny_new_pool(nbr, sizeof(typ))

/*!
** Delete the sent pool
** \param pol The pool to delete
*/
# define			bunny_delete_pool(pol)			\
  bunny_free(pol)

/*!
** Get how many elements there is in the pool.
** \param pool The pool to get the length
** \return The pool size as size_t
*/
# define			bunny_pool_capacity(pool)		\
  ((pool)->nmemb)

/*!
** Get how many busy elements there is in the pool.
** \param pool The pool to get the number of occupied element
** \return The pool amount of occupied elements as size_t
*/
# define			bunny_pool_size(pool)			\
  (pool)->nbr_occupied

/*!
** Test if the pool is empty.
** \param pool The pool to test
** \return True if it is empty
*/
# define			bunny_pool_empty(pool)			\
  (!(pool)->nmemb)

/*!
** Get the size of a single element of the pool
** \param pool The pool to get the size of an element
** \return The element size as size_t
*/
# define			bunny_pool_elem_size(pool)		\
  ((pool)->elemsize)

/*!
** Get the position of the element in the pool.
** \param elem A pointer to the element to inspect.
** \return A size_t that is the current index of the element in the array.
** It may change depending of the life of the pool.
*/
# define			bunny_pool_elem_index(elem)		\
  ((size_t*)elem)[-1]

/*!
** Free all elements in pool but keep the pool.
** \param A pointer on a pool.
*/
# define			bunny_pool_clear(pool)			\
  *(size_t*)&(pool)->nbr_occupied = 0

# define			bunny_pool_get(pool, i, typ)		\
  ((typ*)((pool)->data[(i)]))

/*!
** Get a new element from the pool.
** \param pool The pool to browse.
** \param type The type of the data. No type checking is done!
** \return An available element or NULL if there was none.
*/
# define			bunny_pool_new(pool, type)		\
  (type*)bunny_pool_getv(pool, NULL)

/*!
** Signal that the sent element is free again.
** Pay attention: its fast free mechanism have a cost: it changes the id
** of the last reserved allocation! Its id is now the id of the freed element.
** \param pol The pool to browse.
** \param elem The element to release
*/
void				bunny_pool_free(t_bunny_pool		*pool,
						void			*elem);

typedef void			(*t_bunny_pool_foreach)(void		*node,
							void		*param);

/*!
** Apply a function on every data in the pool.
** \param pol The pool to edit
** \param func A t_bunny_pool_foreach function
** \param par A parameter that will be sent as second parameter of func
*/
void				bunny_pool_foreach(t_bunny_pool		*pool,
						   t_bunny_pool_foreach	func,
						   void			*param);

/*!
** Apply a function on every data in the pool with multiple threads.
** \param pool The thread pool that will share its threads
** \param pool The pool to edit
** \param func The function to apply
** \param param The second parameter sent to func
** \return False to notice you an error happened with threads: all datas
**         were not treated by threads, some of them were treated by the
**         main thread because of thread pool memory exhaustion.
**         True if all was ok.
*/
bool				bunny_pool_fast_foreach(t_bunny_threadpool *the,
							t_bunny_pool	*pool,
							void		(*func)
							(void		*nod,
							 void		*param),
							void		*param);


#endif	/*			__LAPIN_POOL_H__			*/
