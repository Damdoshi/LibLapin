// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

struct			bunny_vector
{
  t_bunny_constructor	ctor;
  t_bunny_destructor	dtor;
  size_t		nmemb;
  size_t		elemsize;
  void			*array;
  /* private */
  size_t		original_nmemb;
  char			data[0];
};

#define			PATTERN		"%zu nmemb, %zu size -> %p"

/*!
** Create a vector storing nmemb elements of a fixed byte size.
**
** When a constructor is provided, it is called for each element. If a
** constructor fails, already constructed elements are destroyed with dtor when
** one was provided.
**
** \param nbr Number of elements to allocate.
** \param siz Size, in bytes, of one element.
** \param ctor Optional constructor called for each element.
** \param dtor Optional destructor called for each element on deletion/shrink.
** \param add User parameter sent to ctor.
** \return A new vector, or NULL on error.
*/
t_bunny_vector		*_bunny_new_vector(size_t			nbr,
					   size_t			siz,
					   t_bunny_constructor		ctor,
					   t_bunny_destructor		dtor,
					   void				*add)
{
  struct bunny_vector	*vec;
  int			i;

  if ((vec = (struct bunny_vector*)bunny_calloc
       (sizeof(struct bunny_vector) + siz * nbr, 1)) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", nbr, siz, vec);
  vec->nmemb = nbr;
  vec->original_nmemb = nbr;
  vec->elemsize = siz;
  vec->array = &vec->data[0];
  vec->ctor = ctor;
  vec->dtor = dtor;
  if (ctor)
    for (i = 0; i < (int)bunny_vector_size(vec); ++i)
      if (ctor(&vec->data[i * siz], add) == false)
	{
	  if (dtor)
	    while (--i >= 0)
	      dtor(&vec->data[i * siz]);
	  bunny_free(vec);
	  return (NULL);
	}
  scream_log_if(PATTERN, "container", nbr, siz, vec);
  return ((t_bunny_vector*)vec);
}

/*!
** Delete a vector.
**
** If the vector has a destructor, it is called once for every element before
** the storage is released.
**
** \param vec The vector to delete.
*/
/**
 * @doc
 * @doc-symbol bunny_delete_vector
 * @doc-kind function
 * @doc-module vector
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a vector.
 * @param vec The vector to delete.
 * @return-success This function does not return a value.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Détruit un vecteur.
 * @param vec Le vecteur à détruire.
 * @return-success Cette fonction ne renvoie pas de valeur.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_vector
 */
void			bunny_delete_vector(t_bunny_vector		*vec)
{
  int			i;

  if (vec->dtor)
    for (i = 0; i < (int)bunny_vector_size(vec); ++i)
      vec->dtor(&((struct bunny_vector*)vec)->data[i * vec->elemsize]);
  bunny_free(vec);
}

#undef			PATTERN
#define			PATTERN		"%p vector, %zu newsize -> %p"

/*!
** Resize a vector.
**
** Shrinking destroys removed elements when a destructor is available. Growing
** may reallocate the vector and constructs new elements when a constructor is
** available. The returned pointer must replace the old one.
**
** \param vec The vector to resize.
** \param newsize The requested number of elements.
** \param add User parameter sent to constructors for new elements.
** \return The resized vector, or NULL on allocation error.
*/
/**
 * @doc
 * @doc-symbol bunny_vector_resize
 * @doc-kind function
 * @doc-module vector
 * @doc-order 280
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Changes the semantic size of a vector.
 * @param vec The vector to resize.
 * @param newsize The requested number of elements.
 * @param add The user pointer forwarded to constructors.
 * @return-success Returns the resized vector.
 * @return-failure Returns $CNULL@ if reallocation or construction fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Change la taille sémantique d'un vecteur.
 * @param vec Le vecteur à redimensionner.
 * @param newsize Le nombre d'éléments demandé.
 * @param add Le pointeur utilisateur transmis aux constructeurs.
 * @return-success Renvoie le vecteur redimensionné.
 * @return-failure Renvoie $CNULL@ si la réallocation ou la construction échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_vector
 */
t_bunny_vector		*bunny_vector_resize(t_bunny_vector		*vec,
					     size_t			newsize,
					     void			*add)
{
  struct bunny_vector	*old, *nw;
  size_t		oldsize;
  size_t		i;

  old = (struct bunny_vector*)vec;
  oldsize = old->nmemb;
  if (newsize <= old->original_nmemb)
    {
      if (newsize < oldsize && vec->dtor)
	for (i = oldsize; i > newsize; --i)
	  vec->dtor(&((struct bunny_vector*)vec)->data[(i - 1) * vec->elemsize]);
      else if (newsize > oldsize && vec->ctor)
	for (i = oldsize; i < newsize; ++i)
	  if (vec->ctor(&((struct bunny_vector*)vec)->data[i * vec->elemsize], add) == false)
	    {
	      if (vec->dtor)
		while (i-- > oldsize)
		  vec->dtor(&((struct bunny_vector*)vec)->data[i * vec->elemsize]);
	      scream_error_if
		(return (vec), BE_CANT_GENERATE_RESSOURCE, PATTERN, "container", vec, newsize, vec);
	    }
      old->nmemb = newsize;
      scream_log_if(PATTERN, "container", vec, newsize, vec);
      return (vec);
    }
  if ((nw = (struct bunny_vector*)bunny_realloc
       (old, sizeof(struct bunny_vector) + newsize * vec->elemsize)) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", vec, newsize, nw);
  nw->array = &nw->data[0];
  vec = (t_bunny_vector*)nw;
  if (vec->ctor)
    for (i = oldsize; i < newsize; ++i)
      if (vec->ctor(&((struct bunny_vector*)vec)->data[i * vec->elemsize], add) == false)
	{
	  if (vec->dtor)
	    while (i-- > oldsize)
	      vec->dtor(&((struct bunny_vector*)vec)->data[i * vec->elemsize]);
	  scream_error_if
	    (return ((t_bunny_vector*)nw), BE_CANT_GENERATE_RESSOURCE, PATTERN, "container", vec, newsize, nw);
	}
  nw->nmemb = newsize;
  nw->original_nmemb = newsize;
  scream_log_if(PATTERN, "container", vec, newsize, nw);
  return ((t_bunny_vector*)nw);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

/*!
** Reallocate a vector so its storage capacity matches its current size.
**
** The returned pointer must replace the old one.
**
** \param vec The vector to crop.
** \return The cropped vector, or NULL on allocation error.
*/
/**
 * @doc
 * @doc-symbol bunny_vector_crop
 * @doc-kind function
 * @doc-module vector
 * @doc-order 300
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Forces vector storage to match its semantic size.
 * @param vec The vector to crop.
 * @return-success Returns the cropped vector.
 * @return-failure Returns $CNULL@ if reallocation fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Force le stockage du vecteur à correspondre à sa taille sémantique.
 * @param vec Le vecteur à rogner.
 * @return-success Renvoie le vecteur rogné.
 * @return-failure Renvoie $CNULL@ si la réallocation échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_vector
 */
t_bunny_vector		*bunny_vector_crop(t_bunny_vector		*vec)
{
  struct bunny_vector	*old, *nw;

  old = (struct bunny_vector*)vec;
  if ((nw = (struct bunny_vector*)bunny_realloc
       (old, sizeof(struct bunny_vector) + vec->nmemb * vec->elemsize)) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", vec, nw);
  nw->array = &nw->data[0];
  nw->original_nmemb = nw->nmemb;
  scream_log_if(PATTERN, "container", vec, nw);
  return ((t_bunny_vector*)nw);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

/*!
** Copy all vector elements into a list.
**
** Each vector element is duplicated with bunny_memdup and pushed in the same
** order into the resulting list. The caller owns both the list and the copied
** element buffers.
**
** \param vec The vector to copy.
** \return A list containing duplicated elements, or NULL on error.
*/
/**
 * @doc
 * @doc-symbol bunny_vector_untie
 * @doc-kind function
 * @doc-module vector
 * @doc-order 360
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Copies all vector elements into a list.
 * @param vec The vector to transform.
 * @return-success Returns a list containing duplicated element data.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_vector
 *
 * @doc-lang fr
 * @brief Copie tous les éléments d'un vecteur dans une liste.
 * @param vec Le vecteur à transformer.
 * @return-success Renvoie une liste contenant des copies des éléments.
 * @return-failure Renvoie $CNULL@ si une allocation échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_vector
 */
t_bunny_list		*bunny_vector_untie(const t_bunny_vector	*vec)
{
  t_bunny_list		*lst = bunny_new_list();
  t_bunny_node		*nod;
  void			*ptr;
  size_t		i;

  if (lst == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", vec, lst);
  for (i = 0; i < bunny_vector_size(vec); ++i)
    {
      if ((ptr = bunny_memdup(bunny_vector_address(vec, i), bunny_vector_elem_size(vec))) == NULL)
	{
	  i = bunny_errno;
	  goto erase_lst;
	}
      if (bunny_list_push_back(lst, ptr) == false)
	{
	  i = bunny_errno;
	  bunny_free(ptr);
	  goto erase_lst;
	}
    }

  scream_log_if(PATTERN, "container", vec, lst);
  return (lst);

 erase_lst:
  for (nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod))
    bunny_free(bunny_list_data(nod, void*));
  bunny_delete_list(lst);
  scream_error_if(return (NULL), i, PATTERN, "container", vec, lst);
  return (NULL);
}

struct			qsort_packet
{
  int			(*cmp)(const void			*a,
			       const void			*b,
			       void				*param);
  void			*ptr;
};

#if			!(_WIN32 || __WIN32__ || __APPLE__)
static int		to_qsort(const void			*a,
				 const void			*b,
				 void				*param)
{
  struct qsort_packet	*pq = (struct qsort_packet*)param;

  return (pq->cmp((void*)a, (void*)b, pq->ptr));
}
#else

void			bunny_shitty_sort(void				*data,
					  size_t			nmemb,
					  size_t			elmsiz,
					  void				*param,
					  t_bunny_comparator		cmp)
{
  char			*buffer = (char *) bunny_alloca(elmsiz);
  char			*ptr;
  bool			sorted;
  size_t		i;
  int			x;

  for (sorted = false; sorted == false; )
    {
      sorted = true;
      for (i = 0; i < nmemb - 1; ++i)
	{
	  ptr = (char*)data;
	  x = cmp(ptr + i * elmsiz, ptr + (i + 1) * elmsiz, param);
	  if (x > 0)
	    {
	      memcpy(&buffer[0], ptr + i * elmsiz, elmsiz);
	      memcpy(ptr + i * elmsiz, ptr + (i + 1) * elmsiz, elmsiz);
	      memcpy(ptr + (i + 1) * elmsiz, &buffer[0], elmsiz);
	      sorted = false;
	    }
	}
    }
  bunny_freea(buffer);
}

#endif

/*!
** Sort a vector in place with a user comparator.
**
** The comparator receives addresses of vector elements and follows the same
** convention as strcmp.
**
** \param vec The vector to sort.
** \param cmp Comparator used to order elements.
** \param param User parameter sent to cmp.
*/
/**
 * @doc
 * @doc-symbol bunny_vector_sort
 * @doc-kind function
 * @doc-module vector
 * @doc-order 340
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sorts a vector in place with a comparison callback.
 * @param vec The vector to sort.
 * @param cmp The comparison callback.
 * @param param The user pointer forwarded to $Scmp@.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_comparator, bunny_list_sort
 *
 * @doc-lang fr
 * @brief Trie un vecteur sur place avec un callback de comparaison.
 * @param vec Le vecteur à trier.
 * @param cmp Le callback de comparaison.
 * @param param Le pointeur utilisateur transmis à $Scmp@.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_comparator, bunny_list_sort
 */
void			bunny_vector_sort(t_bunny_vector		*vec,
					  t_bunny_comparator		cmp,
					  void				*param)
{
  struct qsort_packet	packet;

  packet.cmp = cmp;
  packet.ptr = param;
#if			_WIN32 || __WIN32__ || __APPLE__
  bunny_shitty_sort((void*)vec->array, vec->nmemb, vec->elemsize, param, cmp);
#else
  qsort_r((void*)&((struct bunny_vector*)vec)->data[0], vec->nmemb, vec->elemsize, to_qsort, &packet);
#endif
  scream_log_if("%p vector, %p cmp_func, %p param", "container", vec, cmp, param);
}

/*!
** Apply a function to every element of a vector.
**
** The callback receives the address of each element stored in the vector.
**
** \param vector The vector to browse.
** \param func The function to call on each element.
** \param param User parameter sent to func.
*/
/**
 * @doc
 * @doc-symbol bunny_vector_foreach
 * @doc-kind function
 * @doc-module vector
 * @doc-order 400
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Applies a callback to every element of a vector.
 * @param vec The vector to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @see t_bunny_vector_foreach
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque élément d'un vecteur.
 * @param vec Le vecteur à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @see t_bunny_vector_foreach
 */
void			bunny_vector_foreach(t_bunny_vector	*vector,
					     t_bunny_vector_foreach func,
					     void		*param)
{
  size_t		i;

  for (i = 0; i < bunny_vector_size(vector); ++i)
    func(&((struct bunny_vector*)vector)->data[i * vector->elemsize], param);
}

#undef			PATTERN
#define			PATTERN		"%p threadpool, %p vector, %p func, %p param -> %s"

/*!
** Apply a function to every element of a vector using a thread pool.
**
** If the thread pool cannot accept all tasks, remaining elements are processed
** by the caller thread before waiting for completion.
**
** \param pool The thread pool used to schedule callbacks.
** \param vector The vector to browse.
** \param func The function to call on each element.
** \param param User parameter sent to func.
** \return True if all work was scheduled normally, false if a fallback happened.
*/
/**
 * @doc
 * @doc-symbol bunny_vector_fast_foreach
 * @doc-kind function
 * @doc-module vector
 * @doc-order 420
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Applies a callback to every vector element using a thread pool.
 * @param pool The thread pool used to distribute work.
 * @param vector The vector to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @return-success Returns $Ctrue@ if every task could be scheduled normally.
 * @return-failure Returns $Cfalse@ if some work had to be done by the main thread.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see bunny_thread_wait_completion
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque élément d'un vecteur avec un pool de threads.
 * @param pool Le pool de threads utilisé pour répartir le travail.
 * @param vector Le vecteur à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @return-success Renvoie $Ctrue@ si toutes les tâches ont pu être planifiées normalement.
 * @return-failure Renvoie $Cfalse@ si une partie du travail a dû être faite par le thread principal.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see bunny_thread_wait_completion
 */
bool			bunny_vector_fast_foreach(t_bunny_threadpool *pool,
						  t_bunny_vector *vector,
						  void		(*func)
						  (void		*nod,
						   void		*par),
						  void		*par)
{
  size_t		i;
  int			err;

  for (i = 0; i < bunny_vector_size(vector); ++i)
    if (bunny_thread_push(pool, func, bunny_vector_address(vector, i), par) == false)
      {
	err = bunny_errno;
	while (i < bunny_vector_size(vector))
	  {
	    func(&((struct bunny_vector*)vector)->data[i * vector->elemsize], par);
	    ++i;
	  }
	bunny_thread_wait_completion(pool);
	scream_error_if
	  (return (false), err, PATTERN, "container", pool, vector, func, par, "false");
      }
  bunny_thread_wait_completion(pool);
  scream_log_if(PATTERN, "container", pool, vector, func, par, "true");
  return (true);
}
