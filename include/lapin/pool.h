/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file pool.h
**
**
**
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
#ifndef				__ANSI__
  const void * const		array[0];
#else
  const void * const		array[1];
#endif
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
** \param nmemb How many elements there is in your pool
** \param size What is the type of elements inside your pool
** \return A pool or NULL on error
*/
# define			bunny_new_pool(nbr, typ)		_bunny_new_pool(nbr, sizeof(typ))

/*!
** Delete the sent pool
** \param pol The pool to delete
*/
# define			bunny_delete_pool(pol)			bunny_free(pol)

/*!
** Get how many elements there is in the pool.
** \param pool The pool to get the length
** \return The pool size as size_t
*/
# define			bunny_pool_size(pool)			((pool)->nmemb)

/*!
** Get how many free elements there is in the pool.
** \param pool The pool to get the number of free element
** \return The pool amount of free elements as size_t
*/
# define			bunny_pool_free_elem(pool)		((pool)->nmemb - (pool)->nbr_occupied)

/*!
** Get how many occupied elements there is in the pool.
** \param pool The pool to get the number of occupied element
** \return The pool amount of occupied elements as size_t
*/
# define			bunny_pool_occupied_elem(pool)		(pool)->nbr_occupied

/*!
** Test if the pool is empty.
** \param pool The pool to test
** \return True if it is empty
*/
# define			bunny_pool_empty(pool)			(!(pool)->nmemb)

/*!
** Get the size of a single element of the pool
** \param pool The pool to get the size of an element
** \return The element size as size_t
*/
# define			bunny_pool_elem_size(pool)		((pool)->elemsize)

/*!
** Get a free element inside the pool.
** \param pol The pool to browse.
** \param id A pointer to store the id of the element. Useful when you will release to element.
** \return NULL if there is no free element inside the pool, or a pointer to a free element
**
*/
# define			bunny_pool_getv(pol, id)		\
  ((pol)->nbr_occupied < (pol)->nmemb ?					\
   (void*)(pol)->array[*(id) = (*(size_t*)&(pol)->nbr_occupied)++] :	\
   NULL)

/*!
** Get a free element inside the pool.
** \param pol The pool to browse.
** \param type The type of datas inside the pool
** \return NULL if there is no free element inside the pool, or a pointer to a free element
*/
# define			bunny_pool_get(pol, id, type)		\
  (type*)bunny_pool_getv(pol, id)

/*!
** Signal that the sent element is free again.
** \param pol The pool to browse.
** \param elm The element to release
*/
# define			bunny_pool_release(pol, id)		\
  bunny_swap((void**)&(pol)->array[id], (void**)&(pol)->array		\
	     [(--(*(size_t*)&(pol)->nbr_occupied))])

typedef void			(*t_bunny_pool_foreach)(void		*node,
							void		*param);

/*!
** Apply a function on every data in the pool.
** \param pol The pool to edit
** \param i A free to use size_t
** \param func A t_bunny_pool_foreach function
** \param par A parameter that will be sent as second parameter of func
*/
# define			bunny_pool_foreach(pol, i, func, par)	\
  for (i = 0; i < bunny_pool_occupied_element(pol); ++i)		\
    func((void*)(pol)->array[i], (void*)par);

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
**
** You should use bunny_thread_wait_completion at the end of your thread cycle.

*/
bool				bunny_pool_fast_foreach(t_bunny_threadpool *the,
							t_bunny_pool	*pool,
							void		(*func)
							(void		*nod,
							 const void	*param),
							const void	*param);


#endif	/*			__LAPIN_POOL_H__			*/
