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

/*!
** Partially abstract fixed-capacity pool of pre-reserved elements.
**
** nmemb is the capacity, nbr_occupied is the number of currently reserved
** elements and data stores the internal element slots. Elements are reserved
** and released in constant time, but their internal index may change when an
** element is released.
*/
/*!
** Function called by bunny_pool when an occupied element is released.
**
** Pool destructors are not expected to fail. They are called by
** bunny_pool_free, bunny_pool_clear and bunny_delete_pool.
**
** \param data The element storage to destroy.
*/
/**
 * @doc
 * @doc-symbol t_bunny_pool_destructor
 * @doc-kind type
 * @doc-module pool
 * @doc-order 90
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the destructor callback used by pools.
 * @param data The element storage to destroy.
 * @see bunny_build_pool, bunny_pool_free
 *
 * @doc-lang fr
 * @brief Définit le callback destructeur utilisé par les pools.
 * @param data Le stockage de l'élément à détruire.
 * @see bunny_build_pool, bunny_pool_free
 */
typedef void			(*t_bunny_pool_destructor)(void		*data);

/**
 * @doc
 * @doc-symbol t_bunny_pool
 * @doc-kind type
 * @doc-module pool
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a fixed-capacity pool of pre-reserved elements.
 * @description Releasing an element may move the last occupied slot, so element indices are unstable.
 * @see bunny_new_pool, bunny_pool_new, bunny_pool_free
 *
 * @doc-lang fr
 * @brief Représente un pool à capacité fixe d'éléments pré-réservés.
 * @description Libérer un élément peut déplacer la dernière case occupée, donc les indices sont instables.
 * @see bunny_new_pool, bunny_pool_new, bunny_pool_free
 */
typedef struct			s_bunny_pool
{
  const size_t			magic;
  t_bunny_constructor		ctor;
  t_bunny_pool_destructor	dtor;
  void * const			ctor_param;
  const size_t			nmemb;
  const size_t			elemsize;
  const size_t			allocsize;
  const size_t			nbr_occupied;
  void * const			data[__ZERO_LENGTH__];
}				t_bunny_pool;

/*!
** Create a managed array of maximum nmemb elements of size size.
**
** This is equivalent to _bunny_build_pool with no constructor and no
** destructor.
**
** \param nmemb How many elements there is in your pool
** \param size What is the size of a single element
** \return A pool or NULL on error
*/
t_bunny_pool			*_bunny_new_pool(size_t			nmemb,
						 size_t			size);

/*!
** Create a managed array of maximum nmemb elements of size size.
**
** If ctor is not NULL, it is called every time an element is reserved with
** bunny_pool_getv or bunny_pool_getv_param. If dtor is not NULL, it is called
** every time an occupied element is released, cleared or destroyed. Unlike the
** generic t_bunny_destructor used by vector, a pool destructor returns void:
** once an element release has begun, destruction is expected to succeed.
**
** \param nmemb How many elements there is in your pool
** \param size What is the size of a single element
** \param ctor Optional constructor called when an element is reserved
** \param dtor Optional destructor called when an element is released
** \param add Default parameter sent to ctor by bunny_pool_getv
** \return A pool or NULL on error
*/
t_bunny_pool			*_bunny_build_pool(size_t		nmemb,
						   size_t		size,
						   t_bunny_constructor ctor,
						   t_bunny_pool_destructor dtor,
						   void			*add);

/*!
** Create a managed array of maximum nmemb elements of type typ
** \param nbr How many elements there is in your pool
** \param typ What is the type of elements inside your pool
** \return A pool or NULL on error
*/
/**
 * @doc
 * @doc-symbol bunny_new_pool
 * @doc-kind function
 * @doc-module pool
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a pool of elements of the requested type.
 * @param nbr The maximum number of elements.
 * @param typ The type of one element.
 * @return-success Returns the newly allocated pool.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see t_bunny_pool, bunny_delete_pool
 *
 * @doc-lang fr
 * @brief Crée un pool d'éléments du type demandé.
 * @param nbr Le nombre maximal d'éléments.
 * @param typ Le type d'un élément.
 * @return-success Renvoie le pool nouvellement alloué.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @see t_bunny_pool, bunny_delete_pool
 */
# define			bunny_new_pool(nbr, typ)		\
  _bunny_new_pool(nbr, sizeof(typ))

/*!
** Create a managed array of maximum nmemb elements of type typ with optional
** constructor and destructor callbacks.
** \param nbr How many elements there is in your pool
** \param typ What is the type of elements inside your pool
** \param ctor Optional constructor called when reserving an element
** \param dtor Optional destructor called when releasing an element. It must not fail.
** \param add Default parameter sent to ctor by bunny_pool_getv
** \return A pool or NULL on error
*/
/**
 * @doc
 * @doc-symbol bunny_build_pool
 * @doc-kind function
 * @doc-module pool
 * @doc-order 130
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates a pool with constructor and destructor callbacks.
 * @param nbr The maximum number of elements.
 * @param typ The type of one element.
 * @param ctor The optional constructor called when reserving an element.
 * @param dtor The optional destructor called when releasing an element.
 * @param add The default user pointer forwarded to $Sctor@.
 * @return-success Returns the newly allocated pool.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see t_bunny_pool_destructor, bunny_pool_getv_param
 *
 * @doc-lang fr
 * @brief Crée un pool avec callbacks constructeur et destructeur.
 * @param nbr Le nombre maximal d'éléments.
 * @param typ Le type d'un élément.
 * @param ctor Le constructeur optionnel appelé lors de la réservation d'un élément.
 * @param dtor Le destructeur optionnel appelé lors de la libération d'un élément.
 * @param add Le pointeur utilisateur par défaut transmis à $Sctor@.
 * @return-success Renvoie le pool nouvellement alloué.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @see t_bunny_pool_destructor, bunny_pool_getv_param
 */
# define			bunny_build_pool(nbr, typ, ctor, dtor, add) \
  _bunny_build_pool(nbr, sizeof(typ), ctor, dtor, add)

/*!
** Delete the sent pool.
**
** If the pool has a destructor, it is called on every currently occupied
** element before the storage is released.
**
** \param pol The pool to delete
*/
void				bunny_delete_pool(t_bunny_pool		*pol);

/*!
** Get how many elements there is in the pool.
** \param pool The pool to get the length
** \return The pool size as size_t
*/
/**
 * @doc
 * @doc-symbol bunny_pool_capacity
 * @doc-kind function
 * @doc-module pool
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the maximum number of elements in a pool.
 * @param pool The pool to inspect.
 * @return-success Returns the pool capacity.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Renvoie le nombre maximal d'éléments d'un pool.
 * @param pool Le pool à inspecter.
 * @return-success Renvoie la capacité du pool.
 * @see t_bunny_pool
 */
# define			bunny_pool_capacity(pool)		\
  ((pool)->nmemb)

/*!
** Get how many busy elements there is in the pool.
** \param pool The pool to get the number of occupied element
** \return The pool amount of occupied elements as size_t
*/
/**
 * @doc
 * @doc-symbol bunny_pool_size
 * @doc-kind function
 * @doc-module pool
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the number of occupied pool elements.
 * @param pool The pool to inspect.
 * @return-success Returns the occupied element count.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Renvoie le nombre d'éléments occupés dans un pool.
 * @param pool Le pool à inspecter.
 * @return-success Renvoie le nombre d'éléments occupés.
 * @see t_bunny_pool
 */
# define			bunny_pool_size(pool)			\
  ((pool)->nbr_occupied)

/*!
** Test if the pool currently contains no reserved element.
** \param pool The pool to test
** \return True if it is empty
*/
/**
 * @doc
 * @doc-symbol bunny_pool_empty
 * @doc-kind function
 * @doc-module pool
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests whether a pool contains no occupied element.
 * @param pool The pool to inspect.
 * @return-success Returns $Ctrue@ if the pool is empty.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Teste si un pool ne contient aucun élément occupé.
 * @param pool Le pool à inspecter.
 * @return-success Renvoie $Ctrue@ si le pool est vide.
 * @see t_bunny_pool
 */
# define			bunny_pool_empty(pool)			\
  (!(pool)->nbr_occupied)

/*!
** Get the user size of a single element of the pool.
**
** This is the size that was sent to _bunny_new_pool, or sizeof(typ) when the
** pool was created with bunny_new_pool.
**
** \param pool The pool to get the size of an element
** \return The user element size as size_t
*/
/**
 * @doc
 * @doc-symbol bunny_pool_elem_size
 * @doc-kind function
 * @doc-module pool
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the user size of one pool element.
 * @param pool The pool to inspect.
 * @return-success Returns the element size requested at pool creation.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Renvoie la taille utilisateur d'un élément de pool.
 * @param pool Le pool à inspecter.
 * @return-success Renvoie la taille d'élément demandée à la création du pool.
 * @see t_bunny_pool
 */
# define			bunny_pool_elem_size(pool)		\
  ((pool)->elemsize)

/*!
** Get the internal allocated size of a single pool slot.
**
** This is the previous behaviour of bunny_pool_elem_size: the returned size
** includes the hidden pool metadata stored before each element and the
** alignment padding used internally by the pool.
**
** \param pool The pool to inspect.
** \return The internal slot size as size_t.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_elem_alloc_size
 * @doc-kind function
 * @doc-module pool
 * @doc-order 230
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the internal allocated size of one pool slot.
 * @param pool The pool to inspect.
 * @return-success Returns the slot size including hidden metadata and alignment padding.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Renvoie la taille allouée interne d'une case de pool.
 * @param pool Le pool à inspecter.
 * @return-success Renvoie la taille de case incluant les métadonnées cachées et le padding d'alignement.
 * @see t_bunny_pool
 */
# define			bunny_pool_elem_alloc_size(pool)	\
  ((pool)->allocsize)

/*!
** Get the position of the element in the pool.
** \param elem A pointer to the element to inspect.
** \return A size_t that is the current index of the element in the array.
** It may change depending of the life of the pool.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_elem_index
 * @doc-kind function
 * @doc-module pool
 * @doc-order 240
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the current internal index of a pool element.
 * @param elem The element to inspect.
 * @return-success Returns the element current index.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Renvoie l'indice interne courant d'un élément de pool.
 * @param elem L'élément à inspecter.
 * @return-success Renvoie l'indice courant de l'élément.
 * @see t_bunny_pool
 */
# define			bunny_pool_elem_index(elem)		\
  ((size_t*)elem)[-1]

/*!
** Free all elements in pool but keep the pool.
**
** If the pool has a destructor, it is called on every occupied element before
** the pool is marked empty.
**
** \param pool A pointer on a pool.
*/
void				bunny_pool_clear(t_bunny_pool		*pool);

/*!
** Get the element currently stored at index i.
**
** This does not reserve a new element. Use bunny_pool_new or bunny_pool_getv
** for reservation. The sent type must match the type used to create the pool.
**
** \param pool The pool to browse.
** \param i Index of the occupied element to retrieve.
** \param typ Expected element type.
** \return The typed element pointer.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_get
 * @doc-kind function
 * @doc-module pool
 * @doc-order 370
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns an occupied pool element by index.
 * @param pool The pool to browse.
 * @param i The occupied element index.
 * @param typ The expected element type.
 * @return-success Returns a typed pointer to the occupied element.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Renvoie un élément occupé du pool par indice.
 * @param pool Le pool à parcourir.
 * @param i L'indice de l'élément occupé.
 * @param typ Le type attendu de l'élément.
 * @return-success Renvoie un pointeur typé vers l'élément occupé.
 * @see t_bunny_pool
 */
# define			bunny_pool_get(pool, i, typ)		\
  ((typ*)((pool)->data[(i)]))

/*!
** Reserve a new element from the pool.
**
** If id is not NULL, the current internal index of the reserved element is
** stored in it. This index may change when another element is released. If the
** pool has a constructor, the default parameter provided at pool creation is
** forwarded to it.
**
** \param pool The pool to browse.
** \param id Optional storage for the reserved element index.
** \return An available element or NULL if the pool is full or construction fails.
*/
void				*bunny_pool_getv(t_bunny_pool		*pool,
						 size_t			*id);

/*!
** Reserve a new element from the pool and send param to its constructor.
**
** This behaves like bunny_pool_getv, but param replaces the default parameter
** stored in the pool by bunny_build_pool.
**
** \param pool The pool to browse.
** \param id Optional storage for the reserved element index.
** \param param Parameter forwarded to the optional constructor.
** \return An available element or NULL if the pool is full or construction fails.
*/
void				*bunny_pool_getv_param(t_bunny_pool	*pool,
						       size_t		*id,
						       void		*param);

/*!
** Reserve a new typed element from the pool.
** \param pool The pool to browse.
** \param type The type of the data. No type checking is done!
** \return An available element or NULL if the pool is full.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_new
 * @doc-kind function
 * @doc-module pool
 * @doc-order 280
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reserves one typed element from a pool.
 * @param pool The pool to use.
 * @param type The expected element type.
 * @return-success Returns a typed pointer to the reserved element.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Réserve un élément typé dans un pool.
 * @param pool Le pool à utiliser.
 * @param type Le type attendu de l'élément.
 * @return-success Renvoie un pointeur typé vers l'élément réservé.
 * @see t_bunny_pool
 */
# define			bunny_pool_new(pool, type)		\
  (type*)bunny_pool_getv(pool, NULL)

/*!
** Reserve a new typed element from the pool and send param to its constructor.
** \param pool The pool to browse.
** \param type The type of the data. No type checking is done!
** \param param Parameter forwarded to the optional constructor.
** \return An available element or NULL if the pool is full.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_new_param
 * @doc-kind function
 * @doc-module pool
 * @doc-order 285
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reserves one typed element with an explicit constructor parameter.
 * @param pool The pool to use.
 * @param type The expected element type.
 * @param param The user pointer forwarded to the optional constructor.
 * @return-success Returns a typed pointer to the reserved element.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Réserve un élément typé avec un paramètre constructeur explicite.
 * @param pool Le pool à utiliser.
 * @param type Le type attendu de l'élément.
 * @param param Le pointeur utilisateur transmis au constructeur optionnel.
 * @return-success Renvoie un pointeur typé vers l'élément réservé.
 * @see t_bunny_pool
 */
# define			bunny_pool_new_param(pool, type, param)	\
  (type*)bunny_pool_getv_param(pool, NULL, param)

/*!
** Test if an element is currently reserved inside the sent pool.
**
** This function checks that elem points to the beginning of a pool element,
** belongs to the pool storage and is still inside the occupied range. It can
** be used before bunny_pool_free when the pointer origin is uncertain.
**
** \param pool The pool that should own elem.
** \param elem The element to test.
** \return True if elem is a valid occupied element of pool.
*/
bool				bunny_pool_elem_is_valid(const t_bunny_pool *pool,
							 const void	*elem);

/*!
** Signal that the sent element is free again.
** Pay attention: its fast free mechanism have a cost: it changes the id
** of the last reserved allocation! Its id is now the id of the freed element.
** Invalid elements are rejected instead of corrupting the pool.
** \param pol The pool to browse.
** \param elem The element to release
*/
void				bunny_pool_free(t_bunny_pool		*pool,
						void			*elem);

/*!
** Function called by bunny_pool_foreach and bunny_pool_fast_foreach for each
** occupied element.
*/
/**
 * @doc
 * @doc-symbol t_bunny_pool_foreach
 * @doc-kind type
 * @doc-module pool
 * @doc-order 320
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback used to traverse occupied pool elements.
 * @param node The current occupied element.
 * @param param The user pointer forwarded by traversal.
 * @see bunny_pool_foreach, bunny_pool_fast_foreach
 *
 * @doc-lang fr
 * @brief Définit le callback utilisé pour parcourir les éléments occupés d'un pool.
 * @param node L'élément occupé courant.
 * @param param Le pointeur utilisateur transmis par le parcours.
 * @see bunny_pool_foreach, bunny_pool_fast_foreach
 */
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
** Apply a function on every data in the pool, starting from the last occupied
** element and ending with the first one.
** \param pool The pool to edit
** \param func A t_bunny_pool_foreach function
** \param param A parameter that will be sent as second parameter of func
*/
void				bunny_pool_foreach_reverse(t_bunny_pool	*pool,
							   t_bunny_pool_foreach func,
							   void			*param);

/*!
** Apply a function on every data in the pool while allowing the callback to
** release the current element safely.
**
** The callback may call bunny_pool_free on the node it receives. Inserting new
** elements or releasing arbitrary not-yet-visited elements during this loop is
** not supported.
**
** \param pool The pool to edit
** \param func A t_bunny_pool_foreach function
** \param param A parameter that will be sent as second parameter of func
*/
void				bunny_pool_foreach_safe(t_bunny_pool	*pool,
							 t_bunny_pool_foreach func,
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
							 void			*param);

#endif	/*			__LAPIN_POOL_H__			*/
