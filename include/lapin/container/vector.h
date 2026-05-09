/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file vector.h
** Contiguous array of fixed-size elements.
**
** A vector owns its storage and may optionally call constructors and
** destructors for each element. Unlike stack/list/queue/map, vector elements are
** stored by value, not as container nodes containing user pointers.
*/

#ifndef				__LAPIN_VECTOR_H__
# define			__LAPIN_VECTOR_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure that represent the vector.
*/
/**
 * @doc
 * @doc-symbol t_bunny_vector
 * @doc-kind type
 * @doc-module vector
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a contiguous array of fixed-size elements.
 * @see bunny_new_vector, bunny_build_vector
 *
 * @doc-lang fr
 * @brief Représente un tableau contigu d'éléments de taille fixe.
 * @see bunny_new_vector, bunny_build_vector
 */
typedef struct			s_bunny_vector
{
  t_bunny_constructor		ctor;
  t_bunny_destructor		dtor;
  const size_t			nmemb;
  const size_t			elemsize;
  void * const			array;
}				t_bunny_vector;

/*!
** Create a managed array of nmemb elements of size size.
** Each element will be send to ctor while built.
** Each element will be sent to dtor while destroyed.
** \param nmemb How many elements there is in your vector
** \param size What is the size of a single element
** \param ctor Function to call while building elements
** \param dtor Function to call while destroyed elements
** \param add Parameter sent to ctor
** \return A vector or NULL on error
*/
t_bunny_vector			*_bunny_new_vector(size_t		nmemb,
						   size_t		size,
						   t_bunny_constructor	ctor,
						   t_bunny_destructor	dtor,
						   void			*add);

/*!
** Create a managed array of nmemb elements of type typ. Each element will
** be send to ctor while built. Each element will be sent to dtor while destroyed.
** \param nmemb How many elements there is in your vector
** \param t The type of the elements inside your vector
** \param ctor Function to call while building elements
** \param dtor Function to call while destroyed elements
** \return A vector or NULL on error
*/
/**
 * @doc
 * @doc-symbol bunny_build_vector
 * @doc-kind function
 * @doc-module vector
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates a vector with constructor and destructor callbacks.
 * @param nbr The number of elements.
 * @param t The type of one element.
 * @param ctor The optional constructor callback.
 * @param dtor The optional destructor callback.
 * @param add The user pointer forwarded to $Sctor@.
 * @return-success Returns the newly allocated vector.
 * @return-failure Returns $CNULL@ if allocation or construction fails.
 * @see t_bunny_constructor, t_bunny_destructor
 *
 * @doc-lang fr
 * @brief Crée un vecteur avec callbacks constructeur et destructeur.
 * @param nbr Le nombre d'éléments.
 * @param t Le type d'un élément.
 * @param ctor Le callback constructeur optionnel.
 * @param dtor Le callback destructeur optionnel.
 * @param add Le pointeur utilisateur transmis à $Sctor@.
 * @return-success Renvoie le vecteur nouvellement alloué.
 * @return-failure Renvoie $CNULL@ si l'allocation ou la construction échoue.
 * @see t_bunny_constructor, t_bunny_destructor
 */
# define			bunny_build_vector(nbr, t, ctor, dtor, add) \
  _bunny_new_vector(nbr, sizeof(t), ctor, dtor, add)

/*!
** Create a managed array of nmemb elements of type typ.
** \param nmemb How many elements there is in your vector
** \param t The type of the elements inside your vector
** \return A vector or NULL on error
*/
/**
 * @doc
 * @doc-symbol bunny_new_vector
 * @doc-kind function
 * @doc-module vector
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a vector of elements of the requested type.
 * @param nbr The number of elements.
 * @param t The type of one element.
 * @return-success Returns the newly allocated vector.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see t_bunny_vector, bunny_delete_vector
 *
 * @doc-lang fr
 * @brief Crée un vecteur d'éléments du type demandé.
 * @param nbr Le nombre d'éléments.
 * @param t Le type d'un élément.
 * @return-success Renvoie le vecteur nouvellement alloué.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @see t_bunny_vector, bunny_delete_vector
 */
# define			bunny_new_vector(nbr, t)		\
  _bunny_new_vector(nbr, sizeof(t), NULL, NULL, NULL)

/*!
** Delete the sent vector
** \param vec The vector to delete
*/
void				bunny_delete_vector(t_bunny_vector	*vec);

/*!
** Get how many elements there is in the vector.
** \param vector The vector to get the length
** \return The vector size as size_t
*/
/**
 * @doc
 * @doc-symbol bunny_vector_size
 * @doc-kind function
 * @doc-module vector
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the number of elements in a vector.
 * @param vector The vector to inspect.
 * @return-success Returns the vector size.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Renvoie le nombre d'éléments d'un vecteur.
 * @param vector Le vecteur à inspecter.
 * @return-success Renvoie la taille du vecteur.
 * @see t_bunny_vector
 */
# define			bunny_vector_size(vector)		((vector)->nmemb)

/*!
** Test if the vector is empty.
** \param vector The vector to test
** \return True if it is empty
*/
/**
 * @doc
 * @doc-symbol bunny_vector_empty
 * @doc-kind function
 * @doc-module vector
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests whether a vector is empty.
 * @param vector The vector to inspect.
 * @return-success Returns $Ctrue@ if the vector is empty.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Teste si un vecteur est vide.
 * @param vector Le vecteur à inspecter.
 * @return-success Renvoie $Ctrue@ si le vecteur est vide.
 * @see t_bunny_vector
 */
# define			bunny_vector_empty(vector)		(!(vector)->nmemb)

/*!
** Get the size of a single element of the vector
** \param vector The vector to get the size of an element
** \return The element size as size_t
*/
/**
 * @doc
 * @doc-symbol bunny_vector_elem_size
 * @doc-kind function
 * @doc-module vector
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the size of one vector element.
 * @param vector The vector to inspect.
 * @return-success Returns the element size in bytes.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Renvoie la taille d'un élément de vecteur.
 * @param vector Le vecteur à inspecter.
 * @return-success Renvoie la taille d'un élément en octets.
 * @see t_bunny_vector
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
/**
 * @doc
 * @doc-symbol bunny_vector_data
 * @doc-kind function
 * @doc-module vector
 * @doc-order 240
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads a vector element with the requested type.
 * @param vec The vector to browse.
 * @param nbr The element index.
 * @param typ The expected element type.
 * @return-success Returns the element value directly.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Lit un élément de vecteur avec le type demandé.
 * @param vec Le vecteur à parcourir.
 * @param nbr L'indice de l'élément.
 * @param typ Le type attendu de l'élément.
 * @return-success Renvoie directement la valeur de l'élément.
 * @see t_bunny_vector
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
/**
 * @doc
 * @doc-symbol bunny_vector_address
 * @doc-kind function
 * @doc-module vector
 * @doc-order 260
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the address of a vector element.
 * @param vec The vector to browse.
 * @param nbr The element index.
 * @return-success Returns a $Tvoid@ pointer to the element storage.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Renvoie l'adresse d'un élément de vecteur.
 * @param vec Le vecteur à parcourir.
 * @param nbr L'indice de l'élément.
 * @return-success Renvoie un pointeur $Tvoid@ vers le stockage de l'élément.
 * @see t_bunny_vector
 */
# define			bunny_vector_address(vec, nbr)		(void*)&((char*)(vec)->array)[nbr * vec->elemsize]

/*!
** Resize the sent vector. If newsize is smaller than the previous size, then
** there is no reallocation. If you want to force it to reallocate, use bunny_vector_crop
** directly after bunny_vector_resize.
** \param vec The vector to resize
** \param newsize The new size of the vector
** \param add Parameter sent to ctor
** \return The vector resized. It may have been reallocated, so vec is not valid
**         anymore. Returns NULL on error.
*/
t_bunny_vector			*bunny_vector_resize(t_bunny_vector	*vec,
						     size_t		newsize,
						     void		*add);

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
/**
 * @doc
 * @doc-symbol t_bunny_comparator
 * @doc-kind type
 * @doc-module vector
 * @doc-order 320
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the comparison callback used by vector and list sorting.
 * @param a The first element to compare.
 * @param b The second element to compare.
 * @param param The user pointer forwarded by the sort function.
 * @return-success Returns a negative, zero or positive value like $Sstrcmp@.
 * @see bunny_vector_sort, bunny_list_sort
 *
 * @doc-lang fr
 * @brief Définit le callback de comparaison utilisé par le tri des vecteurs et des listes.
 * @param a Le premier élément à comparer.
 * @param b Le second élément à comparer.
 * @param param Le pointeur utilisateur transmis par la fonction de tri.
 * @return-success Renvoie une valeur négative, nulle ou positive comme $Sstrcmp@.
 * @see bunny_vector_sort, bunny_list_sort
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

/**
 * @doc
 * @doc-symbol t_bunny_vector_foreach
 * @doc-kind type
 * @doc-module vector
 * @doc-order 380
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback used to traverse vector elements.
 * @param node The current element storage.
 * @param param The user pointer forwarded by traversal.
 * @see bunny_vector_foreach, bunny_vector_fast_foreach
 *
 * @doc-lang fr
 * @brief Définit le callback utilisé pour parcourir les éléments d'un vecteur.
 * @param node Le stockage de l'élément courant.
 * @param param Le pointeur utilisateur transmis par le parcours.
 * @see bunny_vector_foreach, bunny_vector_fast_foreach
 */
typedef void			(*t_bunny_vector_foreach)(void		*node,
							  void		*param);

/*!
** Apply a function on every data in the vector.
** \param vec The vector to edit
** \param func A t_bunny_vector_foreach function
** \param par A parameter that will be sent as second parameter of func
*/
void				bunny_vector_foreach(t_bunny_vector	*vec,
						     t_bunny_vector_foreach func,
						     void		*param);

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
							   void		*param),
							  void		*param);

#endif	/*			__LAPIN_VECTOR_H__			*/
