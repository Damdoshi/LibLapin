/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file vector.h
**
**
**
*/

#ifndef				__LAPIN_VECTOR_H__
# define			__LAPIN_VECTOR_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure that represent the vector.
*/
typedef struct			s_bunny_vector
{
  const size_t			nmemb;
  const size_t			elemsize;
  void * const			array;
}				t_bunny_vector;

/*!
** Create a managed array of nmemb elements of size size.
** \param nmemb How many elements there is in your vector
** \param size What is the size of a single element
** \return A vector or NULL on error
*/
t_bunny_vector			*_bunny_new_vector(size_t		nmemb,
						   size_t		size);

/*!
** Create a managed array of nmemb elements of type typ.
** \param nmemb How many elements there is in your vector
** \param t The type of the elements inside your vector
** \return A vector or NULL on error
*/
# define			bunny_new_vector(nbr, t)		_bunny_new_vector(nbr, sizeof(t))

/*!
** Delete the sent vector
** \param vec The vector to delete
*/
# define			bunny_delete_vector(vec)		bunny_free(vec)

/*!
** Get how many elements there is in the vector.
** \param vector The vector to get the length
** \return The vector size as size_t
*/
# define			bunny_vector_size(vector)		((vector)->nmemb)

/*!
** Test if the vector is empty.
** \param vector The vector to test
** \return True if it is empty
*/
# define			bunny_vector_empty(vector)		(!(vector)->nmemb)

/*!
** Get the size of a single element of the vector
** \param vector The vector to get the size of an element
** \return The element size as size_t
*/
# define			bunny_vector_elem_size(vector)		((vector)->elemsize)

/*!
** Get the data that is stored in vec, at index nbr and type it as typ.
** \param vec The vector to browse
** \param nbr The index to fetch
** \param typ The type of the data
** \return The stored data, DIRECTLY (if it is a vector of float, it is a float... and you can use &),
**         not as pointer like others bunny_*_data.
*/
# define			bunny_vector_data(vec, nbr, typ)	((typ*)(vec)->array)[nbr]

/*!
** Get the address of the data that is stored in vec, at index nbr.
** This one allows you to access to data, copy and transmit it even
** without having the type.
** \param vec The vector to browse
** \param nbr The index to fetch
** \return A void* to the address of your data
*/
# define			bunny_vector_address(vec, nbr)		(void*)&((char*)(vec)->array)[nbr * vec->elemsize]

/*!
** Resize the sent vector. If newsize is smaller than the previous size, then
** there is no reallocation. If you want to force it to reallocate, use bunny_vector_crop
** directly after bunny_vector_resize.
** \param vec The vector to resize
** \param newsize The new size of the vector
** \return The vector resized. It may have been reallocated, so vec is not valid
**         anymore. Returns NULL on error.
*/
t_bunny_vector			*bunny_vector_resize(t_bunny_vector	*vec,
						     size_t		newsize);

/*!
** Force the sent vector to have its inner memory chunk size to match its
** semantic size.
** \param vec The vector to crop.
** \return Return the new vector.
*/
t_bunny_vector			*bunny_vector_crop(t_bunny_vector	*vec);

/*!
** The function pointer type used by bunny_vector_sort and bunny_list_sort
** to compare two elements. Return negative, zero or positive in the same
** fashion as strcmp.
*/
typedef int			(*t_bunny_comparator)(const void	*a,
						      const void	*b,
						      void		*param);

/*!
** Sort the sent vector accordingly to the compare function.
** \param vec The source vector
** \param cmp A function pointer that will compare its first param to
**        the second. Works like strcmp. Is of type t_bunny_comparator.
** \param param A pointer that will be send to cmp as third parameter.
*/
void				bunny_vector_sort(t_bunny_vector	*vec,
						  t_bunny_comparator	cmp,
						  void			*param);

struct s_bunny_list;

/*!
** Put all the data inside the sent vector into a list. All datas are duplicated
** so you can delete the vector freely. They are copied with bunny_memdup.
** \param vec The vector to transform
** \return A list that contains every data in the same order than in vector.
*/
struct s_bunny_list		*bunny_vector_untie(const t_bunny_vector *vec);

typedef void			(*t_bunny_vector_foreach)(void		*node,
							  void		*param);

/*!
** Apply a function on every data in the vector.
** \param vec The vector to edit
** \param i A free to use size_t
** \param func A t_bunny_vector_foreach function
** \param par A parameter that will be sent as second parameter of func
*/
# define			bunny_vector_foreach(vec, i, func, par)	\
  for (i = 0; i < bunny_vector_size(vec); ++i)				\
    func(&bunny_vector_data(vec, i, void*), (void*)par);

/*!
** Apply a function on every data in the vector with multiple threads.
** \param pool The thread pool that will share its threads
** \param vector The vector to edit
** \param func The function to apply
** \param param The second parameter sent to func
** \return False to notice you an error happened with threads: all datas
**         were not treated by threads, some of them were treated by the
**         main thread because of thread pool memory exhaustion.
**         True if all was ok.
**
** You should use bunny_thread_wait_completion at the end of your thread cycle.
*/
bool				bunny_vector_fast_foreach(t_bunny_threadpool *pool,
							  t_bunny_vector *vector,
							  void		(*func)
							  (void		*nod,
							   const void	*param),
							  const void	*param);

#endif	/*			__LAPIN_VECTOR_H__			*/
