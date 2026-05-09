// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stddef.h>
#include		<stdint.h>
#include		<string.h>
#include		"lapin_private.h"

#ifndef			BUNNY_POOL_DEBUG
# define		BUNNY_POOL_DEBUG	0
#endif

#define			POOL_MAGIC_ALIVE	((size_t)0xB00B1E50u)
#define			POOL_MAGIC_DEAD		((size_t)0xDEAD1E50u)
#define			POOL_ALLOC_PATTERN	0xA5
#define			POOL_FREE_PATTERN	0xDD

struct			bunny_pool
{
  size_t		magic;
  t_bunny_constructor	ctor;
  t_bunny_pool_destructor dtor;
  void			*ctor_param;
  size_t		nmemb;
  size_t		elemsize;
  size_t		allocsize;
  size_t		nbr_occupied;
  void			*array[0];
  // Followed by nmemb ptr
  // Followed by alignment padding
  // Followed by nmemb * allocsize bytes
};

#define			PATTERN		"%zu nmemb, %zu size -> %p"

static size_t		align_size(size_t			size,
				   size_t			align)
{
  const size_t		mod = size % align;

  if (mod == 0)
    return (size);
  return (size + align - mod);
}

static char		*align_ptr(char				*ptr,
				   size_t			align)
{
  const uintptr_t	addr = (uintptr_t)ptr;
  const uintptr_t	mod = addr % align;

  if (mod == 0)
    return (ptr);
  return ((char*)(addr + align - mod));
}

static size_t		pool_alignment(void)
{
  return (alignof(max_align_t));
}

static size_t		pool_header_size(void)
{
  return (align_size(sizeof(size_t), pool_alignment()));
}

static char		*pool_storage(const struct bunny_pool	*pool)
{
  return (align_ptr((char*)&pool->array[pool->nmemb], pool_alignment()));
}

static bool		pool_is_alive(const struct bunny_pool	*pool)
{
  if (pool == NULL)
    return (false);
#if BUNNY_POOL_DEBUG
  return (pool->magic == POOL_MAGIC_ALIVE);
#else
  return (true);
#endif
}

static void		pool_poison(void			*ptr,
				    size_t			size,
				    unsigned char		pattern)
{
#if BUNNY_POOL_DEBUG
  memset(ptr, pattern, size);
#else
  (void)ptr;
  (void)size;
  (void)pattern;
#endif
}

static void		*pool_getv(t_bunny_pool			*pol,
				   size_t			*id,
				   void				*param)
{
  struct bunny_pool	*pool = (struct bunny_pool*)pol;
  void			*ret;

  if (!pool_is_alive(pool))
    scream_error_if(return (NULL), BE_BAD_ADDRESS, "%p pool", "container", pol);
  if (pool->nbr_occupied >= pool->nmemb)
    return (NULL);
  ret = pool->array[pool->nbr_occupied];
  pool_poison(ret, pool->elemsize, POOL_ALLOC_PATTERN);
  if (pool->ctor && pool->ctor(ret, param) == false)
    {
      pool_poison(ret, pool->elemsize, POOL_FREE_PATTERN);
      scream_error_if(return (NULL), BE_CANT_GENERATE_RESSOURCE, "%p pool", "container", pol);
    }
  if (id)
    *id = ((size_t*)ret)[-1];
  pool->nbr_occupied += 1;
  return (ret);
}

/*!
** Create a fixed capacity pool of equally sized elements.
**
** A pool performs constant-time reservation and release by swapping element
** slots internally. Element indices may change when another element is freed.
**
** \param nmemb Maximum number of elements in the pool.
** \param size Size, in bytes, of one element.
** \return A new pool, or NULL on allocation error.
*/
t_bunny_pool		*_bunny_new_pool(size_t			nmemb,
					 size_t			size)
{
  return (_bunny_build_pool(nmemb, size, NULL, NULL, NULL));
}

/*!
** Create a fixed capacity pool of equally sized elements.
**
** Constructors and destructors are called when elements are reserved and
** released, not when the pool storage itself is created.
**
** \param nmemb Maximum number of elements in the pool.
** \param size Size, in bytes, of one element.
** \param ctor Optional constructor called when reserving an element.
** \param dtor Optional destructor called when releasing an element. It must not fail.
** \param add Default parameter sent to ctor by bunny_pool_getv.
** \return A new pool, or NULL on allocation error.
*/
t_bunny_pool		*_bunny_build_pool(size_t			nmemb,
					   size_t			size,
					   t_bunny_constructor	ctor,
					   t_bunny_pool_destructor dtor,
					   void				*add)
{
  struct bunny_pool	*pol;
  char			*ptr;
  size_t		i;

  const size_t		user_size = size;
  const size_t		header_size = pool_header_size();
  const size_t		alloc_size = align_size(header_size + user_size, pool_alignment());

  if ((pol = (struct bunny_pool*)bunny_malloc
       (i = sizeof(struct bunny_pool)
	+ alloc_size * nmemb
	+ nmemb * sizeof(pol->array[0])
	+ pool_alignment() - 1)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "container", nmemb, user_size, (void*)NULL);
  memset(pol, 0, i);
  pol->magic = POOL_MAGIC_ALIVE;
  pol->ctor = ctor;
  pol->dtor = dtor;
  pol->ctor_param = add;
  pol->nmemb = nmemb;
  pol->elemsize = user_size;
  pol->allocsize = alloc_size;
  pol->nbr_occupied = 0;
  for (ptr = pool_storage(pol), i = 0; i < nmemb; ++i, ptr = &ptr[alloc_size])
    {
      *((size_t*)&ptr[header_size - sizeof(size_t)]) = i;
      pol->array[i] = (void*)&ptr[header_size];
      pool_poison(pol->array[i], pol->elemsize, POOL_FREE_PATTERN);
    }
  scream_log_if(PATTERN, "container", nmemb, user_size, pol);
  return ((t_bunny_pool*)pol);
}

#undef			PATTERN
#define			PATTERN		"%p pool, %zu id -> %p"

/*!
** Reserve one free element from a pool.
**
** The returned pointer is valid until it is released with bunny_pool_free or
** until the pool is destroyed. If id is not NULL, the current internal index is
** stored in it.
**
** \param pol The pool to browse.
** \param id Optional storage for the current element index.
** \return A free element, or NULL if the pool is full.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_getv
 * @doc-kind function
 * @doc-module pool
 * @doc-order 380
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reserves one available element from a pool.
 * @param pool The pool to use.
 * @param id Optional storage for the current internal index.
 * @return-success Returns the reserved element storage.
 * @return-failure Returns $CNULL@ if the pool is full or construction fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Réserve un élément disponible dans un pool.
 * @param pool Le pool à utiliser.
 * @param id Stockage optionnel de l'indice interne courant.
 * @return-success Renvoie le stockage de l'élément réservé.
 * @return-failure Renvoie $CNULL@ si le pool est plein ou si la construction échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_pool
 */
void			*bunny_pool_getv(t_bunny_pool		*pol,
					 size_t			*id)
{
  struct bunny_pool	*pool = (struct bunny_pool*)pol;
  void			*ret;

  ret = pool_getv(pol, id, pool ? pool->ctor_param : NULL);
  scream_log_if(PATTERN, "container", pol, id ? *id : (size_t)-1, ret);
  return (ret);
}

/*!
** Reserve one free element from a pool and send param to its constructor.
**
** \param pol The pool to browse.
** \param id Optional storage for the current element index.
** \param param Parameter sent to the optional constructor.
** \return A free element, or NULL if the pool is full or construction fails.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_getv_param
 * @doc-kind function
 * @doc-module pool
 * @doc-order 385
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Reserves one pool element with an explicit constructor parameter.
 * @param pool The pool to use.
 * @param id Optional storage for the current internal index.
 * @param param The user pointer forwarded to the optional constructor.
 * @return-success Returns the reserved element storage.
 * @return-failure Returns $CNULL@ if the pool is full or construction fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Réserve un élément de pool avec un paramètre constructeur explicite.
 * @param pool Le pool à utiliser.
 * @param id Stockage optionnel de l'indice interne courant.
 * @param param Le pointeur utilisateur transmis au constructeur optionnel.
 * @return-success Renvoie le stockage de l'élément réservé.
 * @return-failure Renvoie $CNULL@ si le pool est plein ou si la construction échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_pool
 */
void			*bunny_pool_getv_param(t_bunny_pool	*pol,
					       size_t		*id,
					       void		*param)
{
  void			*ret;

  ret = pool_getv(pol, id, param);
  scream_log_if(PATTERN, "container", pol, id ? *id : (size_t)-1, ret);
  return (ret);
}

/*!
** Test if an element is currently reserved inside a pool.
**
** The test is constant-time: the element address is checked against the pool
** storage, then the embedded dense index is cross-checked with the pool array.
**
** \param pol The pool that should own the element.
** \param elem The element to test.
** \return True if elem is an occupied element of pol.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_elem_is_valid
 * @doc-kind function
 * @doc-module pool
 * @doc-order 395
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Tests whether a pointer is an occupied element of a pool.
 * @param pool The pool that should own the element.
 * @param elem The element pointer to test.
 * @return-success Returns $Ctrue@ if the pointer is a valid occupied element.
 * @return-failure Returns $Cfalse@ otherwise.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Teste si un pointeur est un élément occupé d'un pool.
 * @param pool Le pool qui devrait posséder l'élément.
 * @param elem Le pointeur d'élément à tester.
 * @return-success Renvoie $Ctrue@ si le pointeur est un élément occupé valide.
 * @return-failure Renvoie $Cfalse@ sinon.
 * @see t_bunny_pool
 */
bool			bunny_pool_elem_is_valid(const t_bunny_pool	*pol,
					 const void			*elem)
{
  const struct bunny_pool *pool = (const struct bunny_pool*)pol;
  const size_t		header_size = pool_header_size();
  uintptr_t		storage;
  const uintptr_t	user = (uintptr_t)elem;
  uintptr_t		slot;
  size_t		index;

  if (!pool_is_alive(pool) || elem == NULL || pool->allocsize == 0)
    return (false);
  storage = (uintptr_t)pool_storage(pool);
  if (user < storage + header_size)
    return (false);
  slot = user - header_size;
  if (slot < storage || slot >= storage + pool->allocsize * pool->nmemb)
    return (false);
  if ((slot - storage) % pool->allocsize != 0)
    return (false);
  index = ((const size_t*)elem)[-1];
  if (index >= pool->nbr_occupied)
    return (false);
  return (pool->array[index] == elem);
}

#undef			PATTERN
#define			PATTERN		"%p pool, %p elem"

/*!
** Release an element previously reserved from a pool.
**
** The pool keeps release constant-time by swapping the freed slot with the last
** occupied slot, so element indices may change after this call. Invalid
** elements are rejected instead of corrupting the pool.
**
** \param pol The pool that owns the element.
** \param elem The element to release.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_free
 * @doc-kind function
 * @doc-module pool
 * @doc-order 300
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Releases one occupied element back to a pool.
 * @param pool The pool that owns the element.
 * @param elem The element to release.
 * @return-success This function does not return a value.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Libère un élément occupé vers son pool.
 * @param pool Le pool qui possède l'élément.
 * @param elem L'élément à libérer.
 * @return-success Cette fonction ne renvoie pas de valeur.
 * @see t_bunny_pool
 */
void			bunny_pool_free(t_bunny_pool		*pol,
					void			*elem)
{
  struct bunny_pool	*pool = (struct bunny_pool*)pol;
  size_t		*e;

  if (!bunny_pool_elem_is_valid(pol, elem))
    scream_error_if(return, BE_BAD_ADDRESS, PATTERN, "container", pol, elem);
  if (pool->dtor)
    pool->dtor(elem);
  pool_poison(elem, pool->elemsize, POOL_FREE_PATTERN);
  e = &(((size_t*)elem)[-1]);
  pool->nbr_occupied -= 1;
  bunny_swap(&pool->array[*e], &pool->array[pool->nbr_occupied]);

  ((size_t*)pool->array[*e])[-1] = *e;
  ((size_t*)pool->array[pool->nbr_occupied])[-1] = pool->nbr_occupied;
}

#undef			PATTERN
#define			PATTERN		"%p pool"

/*!
** Release all occupied elements from a pool without deleting the pool itself.
**
** \param pol The pool to clear.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_clear
 * @doc-kind function
 * @doc-module pool
 * @doc-order 260
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Releases every occupied element while keeping the pool.
 * @param pool The pool to clear.
 * @return-success This function does not return a value.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Libère tous les éléments occupés en conservant le pool.
 * @param pool Le pool à vider.
 * @return-success Cette fonction ne renvoie pas de valeur.
 * @see t_bunny_pool
 */
void			bunny_pool_clear(t_bunny_pool		*pol)
{
  struct bunny_pool	*pool = (struct bunny_pool*)pol;
  size_t		i;

  if (!pool_is_alive(pool))
    scream_error_if(return, BE_BAD_ADDRESS, PATTERN, "container", pol);
  if (pool->dtor)
    for (i = pool->nbr_occupied; i > 0; --i)
      pool->dtor(pool->array[i - 1]);
  for (i = 0; i < pool->nbr_occupied; ++i)
    pool_poison(pool->array[i], pool->elemsize, POOL_FREE_PATTERN);
  pool->nbr_occupied = 0;
}

/*!
** Delete a pool.
**
** \param pol The pool to delete.
*/
/**
 * @doc
 * @doc-symbol bunny_delete_pool
 * @doc-kind function
 * @doc-module pool
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a pool and releases its storage.
 * @param pol The pool to delete.
 * @return-success This function does not return a value.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Détruit un pool et libère son stockage.
 * @param pol Le pool à détruire.
 * @return-success Cette fonction ne renvoie pas de valeur.
 * @see t_bunny_pool
 */
void			bunny_delete_pool(t_bunny_pool		*pol)
{
  struct bunny_pool	*pool = (struct bunny_pool*)pol;

  if (pol == NULL)
    return;
  bunny_pool_clear(pol);
  pool->magic = POOL_MAGIC_DEAD;
  bunny_free(pool);
}

/*!
** Apply a function to every occupied element of a pool.
**
** \param pool The pool to browse.
** \param func The function to call on each occupied element.
** \param param User parameter sent to func.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_foreach
 * @doc-kind function
 * @doc-module pool
 * @doc-order 340
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Applies a callback to every occupied pool element.
 * @param pool The pool to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @return-success This function does not return a value.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque élément occupé d'un pool.
 * @param pool Le pool à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @return-success Cette fonction ne renvoie pas de valeur.
 * @see t_bunny_pool
 */
void			bunny_pool_foreach(t_bunny_pool		*pool,
					   t_bunny_pool_foreach	func,
					   void			*param)
{
  size_t		i;

  for (i = 0; i < bunny_pool_size(pool); ++i)
    func(pool->data[i], param);
}

/*!
** Apply a function to every occupied element of a pool in reverse order.
**
** \param pool The pool to browse.
** \param func The function to call on each occupied element.
** \param param User parameter sent to func.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_foreach_reverse
 * @doc-kind function
 * @doc-module pool
 * @doc-order 345
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Applies a callback to occupied pool elements from last to first.
 * @param pool The pool to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @return-success This function does not return a value.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Applique un callback aux éléments occupés du pool du dernier au premier.
 * @param pool Le pool à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @return-success Cette fonction ne renvoie pas de valeur.
 * @see t_bunny_pool
 */
void			bunny_pool_foreach_reverse(t_bunny_pool	*pool,
						   t_bunny_pool_foreach func,
						   void			*param)
{
  size_t		i;

  for (i = bunny_pool_size(pool); i > 0; --i)
    func(pool->data[i - 1], param);
}

/*!
** Apply a function to every occupied element while allowing the callback to
** release the current element.
**
** \param pool The pool to browse.
** \param func The function to call on each occupied element.
** \param param User parameter sent to func.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_foreach_safe
 * @doc-kind function
 * @doc-module pool
 * @doc-order 350
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Traverses a pool while allowing the callback to release the current element.
 * @param pool The pool to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @return-success This function does not return a value.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Parcourt un pool en autorisant le callback à libérer l'élément courant.
 * @param pool Le pool à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @return-success Cette fonction ne renvoie pas de valeur.
 * @see t_bunny_pool
 */
void			bunny_pool_foreach_safe(t_bunny_pool	*pool,
						 t_bunny_pool_foreach func,
						 void			*param)
{
  bunny_pool_foreach_reverse(pool, func, param);
}

#undef			PATTERN
#define			PATTERN		"%p threadpool, %p pool, %p func, %p par -> %s"

/*!
** Apply a function to every occupied element of a pool using a thread pool.
**
** If the thread pool cannot accept all tasks, remaining elements are processed
** by the caller thread before waiting for completion.
**
** \param the The thread pool used to schedule callbacks.
** \param pool The pool to browse.
** \param func The function to call on each occupied element.
** \param par User parameter sent to func.
** \return True if all work was scheduled normally, false if a fallback happened.
*/
/**
 * @doc
 * @doc-symbol bunny_pool_fast_foreach
 * @doc-kind function
 * @doc-module pool
 * @doc-order 360
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Applies a callback to every occupied pool element using a thread pool.
 * @param the The thread pool used to distribute work.
 * @param pool The pool to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @return-success Returns $Ctrue@ if every task could be scheduled normally.
 * @return-failure Returns $Cfalse@ if some work had to be done by the main thread.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_pool
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque élément occupé d'un pool avec un pool de threads.
 * @param the Le pool de threads utilisé pour répartir le travail.
 * @param pool Le pool à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @return-success Renvoie $Ctrue@ si toutes les tâches ont pu être planifiées normalement.
 * @return-failure Renvoie $Cfalse@ si une partie du travail a dû être faite par le thread principal.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_pool
 */
bool			bunny_pool_fast_foreach(t_bunny_threadpool *the,
						 t_bunny_pool	*pool,
						 void		(*func)
						 (void		*nod,
						  void		*par),
						 void		*par)
{
  size_t		i;
  int			err;

  for (i = 0; i < bunny_pool_size(pool); ++i)
    if (bunny_thread_push(the, func, (void*)pool->data[i], par) == false)
      {
	err = bunny_errno;
	while (i < bunny_pool_size(pool))
	  {
	    func((void*)pool->data[i], par);
	    ++i;
	  }
	bunny_thread_wait_completion(the);
	scream_error_if(return (false), err, PATTERN, "container", the, pool, func, par, "false");
      }
  bunny_thread_wait_completion(the);
  scream_log_if(PATTERN, "container", the, pool, func, par, "true");
  return (true);
}
