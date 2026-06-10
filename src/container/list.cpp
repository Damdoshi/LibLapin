// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

struct			bunny_node
{
  void			*data;
  struct bunny_node	*next;
  struct bunny_node	*prev;
};

struct			bunny_list
{
  size_t		length;
  struct bunny_node	*front;
  struct bunny_node	*back;
};

/*!
** Delete a list and all of its internal nodes.
**
** Stored data pointers are not freed. Only the container nodes and the list
** object itself are released.
**
** \param list The list to destroy.
** \return The number of elements that were stored in the list.
*/
/**
 * @doc
 * @doc-symbol bunny_delete_list
 * @doc-kind function
 * @doc-module list
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a list and its internal nodes.
 * @param list The list to delete.
 * @return-success Returns the number of elements that were in the list.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see bunny_new_list
 *
 * @doc-lang fr
 * @brief Détruit une liste et ses nœuds internes.
 * @param list La liste à détruire.
 * @return-success Renvoie le nombre d'éléments qui étaient dans la liste.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see bunny_new_list
 */
size_t			bunny_delete_list(t_bunny_list		*list)
{
  struct bunny_node	*nod, *prev;
  size_t		siz = list->length;

  nod = (struct bunny_node*)list->front;
  while (nod != NULL)
    {
      prev = nod->next;
      bunny_free(nod);
      nod = prev;
    }
  bunny_free(list);
  scream_log_if("%p -> %zu", "container", list, siz);
  return (siz);
}

#define			PATTERN		"%p list, %p data -> %s"

/*!
** Push a data pointer at the front of a list.
**
** This is the typed implementation behind the bunny_list_push_front macro.
**
** \param list The list to edit.
** \param data The data pointer to store.
** \return True on success, false on allocation error.
*/
bool			_bunny_list_push_front(t_bunny_list	*list,
					       const void	*data)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod = (struct bunny_node*)bunny_malloc(sizeof(*nod));

  if (nod == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, "container", list, data, "false");
  nod->prev = NULL;
  nod->next = lst->front;
  if (lst->front != NULL)
    lst->front->prev = nod;
  lst->front = nod;
  if (lst->back == NULL)
    lst->back = nod;
  nod->data = (void*)data;
  lst->length += 1;
  scream_log_if(PATTERN, "container", list, data, "true");
  return (true);
}

/*!
** Push a data pointer at the back of a list.
**
** This is the typed implementation behind the bunny_list_push_back macro.
**
** \param list The list to edit.
** \param data The data pointer to store.
** \return True on success, false on allocation error.
*/
bool			_bunny_list_push_back(t_bunny_list	*list,
					      const void	*data)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod = (struct bunny_node*)bunny_malloc(sizeof(*nod));

  if (nod == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, "container", list, data, "false");
  nod->next = NULL;
  nod->prev = lst->back;
  if (lst->back != NULL)
    lst->back->next = nod;
  lst->back = nod;
  if (lst->front == NULL)
    lst->front = nod;
  nod->data = (void*)data;
  lst->length += 1;
  scream_log_if(PATTERN, "container", list, data, "true");
  return (true);
}

/*!
** Pop the data pointer stored at the front of a list.
**
** The returned data is not freed by the container.
**
** \param list The list to edit.
** \return The extracted data pointer, or NULL if the list is empty.
*/
void			*_bunny_list_pop_front(t_bunny_list	*list)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod;
  void			*dat;

  if ((nod = lst->front) == NULL)
    scream_error_if(return (NULL), BE_CONTAINER_IS_EMPTY, "%p -> %p", "container", list, nod);
  if ((lst->front = nod->next) != NULL)
    lst->front->prev = NULL;
  else
    lst->back = NULL;
  dat = nod->data;
  bunny_free(nod);
  lst->length -= 1;
  scream_log_if("%p -> %p", "container", list, dat);
  return (dat);
}

/*!
** Pop the data pointer stored at the back of a list.
**
** The returned data is not freed by the container.
**
** \param list The list to edit.
** \return The extracted data pointer, or NULL if the list is empty.
*/
void			*_bunny_list_pop_back(t_bunny_list	*list)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod;
  void			*dat;

  if ((nod = lst->back) == NULL)
    scream_error_if(return (NULL), BE_CONTAINER_IS_EMPTY, "%p -> %p", "container", list, nod);
  if ((lst->back = nod->prev) != NULL)
    lst->back->next = NULL;
  else
    lst->front = NULL;
  dat = nod->data;
  bunny_free(nod);
  lst->length -= 1;
  scream_log_if("%p -> %p", "container", list, dat);
  return (dat);
}

#undef			PATTERN
#define			PATTERN		"%p list, %p filter_function, %p param -> %p"

/*!
** Create a list containing the elements accepted by a filter function.
**
** The data pointers are copied as pointers; pointed data is not duplicated.
** The returned list must be deleted with bunny_delete_list.
**
** \param list The source list.
** \param filter Function called for each stored data pointer.
** \param param User parameter sent to filter.
** \return A new list containing matching elements, or NULL on error.
*/
/**
 * @doc
 * @doc-symbol bunny_list_filter
 * @doc-kind function
 * @doc-module list
 * @doc-order 360
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Builds a new list with elements accepted by a filter.
 * @param list The source list.
 * @param filter The predicate called for each data pointer.
 * @param param The user pointer forwarded to $Sfilter@.
 * @return-success Returns a new list filled with matching data pointers.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see bunny_new_list, bunny_delete_list
 *
 * @doc-lang fr
 * @brief Construit une nouvelle liste avec les éléments acceptés par un filtre.
 * @param list La liste source.
 * @param filter Le prédicat appelé pour chaque pointeur de donnée.
 * @param param Le pointeur utilisateur transmis à $Sfilter@.
 * @return-success Renvoie une nouvelle liste remplie avec les pointeurs correspondants.
 * @return-failure Renvoie $CNULL@ si une allocation échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see bunny_new_list, bunny_delete_list
 */
t_bunny_list		*bunny_list_filter(t_bunny_list		*list,
					   bool			(*filter)
					   (const void		*lst,
					    void		*param),
					   void			*param)
{
  t_bunny_list		*lst = bunny_new_list();
  t_bunny_node		*node;

  if (lst == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "container", list, filter, param, lst);
  for (node = bunny_list_begin(list); node != NULL; node = bunny_list_next(node))
    if (filter(node->data, param))
      if (bunny_list_push_back(lst, node->data) == false)
	{
	  bunny_delete_list(lst);
	  scream_error_if
	    (return (NULL), bunny_errno, PATTERN, "container", list, filter, param, (void*)NULL);
	}
  scream_log_if(PATTERN, "container", list, filter, param, lst);
  return (lst);
}

struct			qsort_packet
{
  int			(*cmp)(const void			*a,
			       const void			*b,
			       void				*param);
  void			*ptr;
};

static int		to_qsort(const void			*a,
				 const void			*b,
				 void				*param)
{
  struct qsort_packet	*pq = (struct qsort_packet*)param;

  return (pq->cmp(*(void**)a, *(void**)b, pq->ptr));
}

#if			_WIN32 || __WIN32__ || __APPLE__

void			bunny_shitty_sort(void			*data,
					  size_t		nmemb,
					  size_t		elmsiz,
					  void			*param,
					  t_bunny_comparator	cmp);

#endif

/*!
** Sort a list in place with a user comparator.
**
** The comparator follows the same convention as strcmp: negative if a should
** be ordered before b, zero if they compare equal, positive otherwise.
**
** \param list The list to sort.
** \param cmp Comparator used to order stored data pointers.
** \param param User parameter sent to cmp.
*/
/**
 * @doc
 * @doc-symbol bunny_list_sort
 * @doc-kind function
 * @doc-module list
 * @doc-order 380
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sorts a list in place with a comparison callback.
 * @param list The list to sort.
 * @param cmp The comparison callback.
 * @param param The user pointer forwarded to $Scmp@.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_comparator, bunny_vector_sort
 *
 * @doc-lang fr
 * @brief Trie une liste sur place avec un callback de comparaison.
 * @param list La liste à trier.
 * @param cmp Le callback de comparaison.
 * @param param Le pointeur utilisateur transmis à $Scmp@.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_comparator, bunny_vector_sort
 */
void			bunny_list_sort(t_bunny_list		*list,
					int			(*cmp)
					(const void		*a,
					 const void		*b,
					 void			*param),
					void			*param)
{
  struct qsort_packet	packet;
  void			**array = (void**)bunny_alloca(bunny_list_size(list) * sizeof(*array));
  t_bunny_node		*node;
  size_t		i;

  for (node = bunny_list_begin(list), i = 0; node != NULL; node = bunny_list_next(node), ++i)
    array[i] = (void*)node->data;
  packet.cmp = cmp;
  packet.ptr = param;
#if			_WIN32 || __WIN32__ || __APPLE__
  bunny_shitty_sort(array, bunny_list_size(list), sizeof(*array), &packet, to_qsort);
#else
  qsort_r(array, bunny_list_size(list), sizeof(*array), to_qsort, &packet);
#endif
  for (node = bunny_list_begin(list), i = 0; node != NULL; node = bunny_list_next(node), ++i)
    node->data = (void*)array[i];
  scream_log_if("%p list, %p compare_function, %p param", "container", list, cmp, param);
  bunny_freea(array);
}

#undef			PATTERN
#define			PATTERN		"%p list, %zu data_size -> %p"

/*!
** Copy the content of a list into a vector.
**
** Each stored pointer is treated as the address of an element of elemsize
** bytes. The bytes are copied into the resulting vector in list order.
**
** \param lst The list to copy.
** \param elemsize The size, in bytes, of one copied element.
** \return A vector containing copied elements, or NULL on error.
*/
t_bunny_vector		*_bunny_list_tie(const t_bunny_list	*lst,
					 size_t			elemsize)
{
  t_bunny_vector	*vec;
  t_bunny_node		*nod;
  size_t		i;

  if ((vec = _bunny_new_vector
       (bunny_list_size(lst), elemsize, NULL, NULL, NULL)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "container", lst, elemsize, vec);
  for (nod = bunny_list_begin(lst), i = 0; nod != NULL; nod = bunny_list_next(nod), ++i)
    memcpy(bunny_vector_address(vec, i), bunny_list_data(nod, void*), elemsize);
  scream_log_if(PATTERN, "container", lst, elemsize, vec);
  return (vec);
}

/*!
** Apply a function to every node of a list.
**
** The callback receives the t_bunny_node pointer, not directly the stored data.
** Use bunny_list_data inside the callback to retrieve the value.
**
** \param lst The list to browse.
** \param func The function to call on each node.
** \param param User parameter sent to func.
*/
/**
 * @doc
 * @doc-symbol bunny_list_foreach
 * @doc-kind function
 * @doc-module list
 * @doc-order 540
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Applies a callback to every data pointer in a list.
 * @param list The list to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @see t_bunny_list_foreach
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque pointeur de donnée d'une liste.
 * @param list La liste à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @see t_bunny_list_foreach
 */
void			bunny_list_foreach(t_bunny_list		*lst,
					   t_bunny_list_foreach func,
					   void			*param)
{
  t_bunny_node		*nod;

  for (nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod))
    func(bunny_list_data(nod, void*), (void*)param);
}


#undef			PATTERN
#define			PATTERN		"%p threadpool, %p list, %p func, %p param -> %s"

/*!
** Apply a function to every node of a list using a thread pool.
**
** The callback receives the t_bunny_node pointer, not directly the stored data.
** If the thread pool cannot accept all tasks, remaining nodes are processed by
** the caller thread before waiting for completion.
**
** \param pool The thread pool used to schedule callbacks.
** \param list The list to browse.
** \param func The function to call on each node.
** \param param User parameter sent to func.
** \return True if all work was scheduled normally, false if a fallback happened.
*/
/**
 * @doc
 * @doc-symbol bunny_list_fast_foreach
 * @doc-kind function
 * @doc-module list
 * @doc-order 560
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Applies a callback to every list data pointer using a thread pool.
 * @param pool The thread pool used to distribute work.
 * @param list The list to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @return-success Returns $Ctrue@ if every task could be scheduled normally.
 * @return-failure Returns $Cfalse@ if some work had to be done by the main thread.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see bunny_thread_wait_completion
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque donnée d'une liste avec un pool de threads.
 * @param pool Le pool de threads utilisé pour répartir le travail.
 * @param list La liste à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @return-success Renvoie $Ctrue@ si toutes les tâches ont pu être planifiées normalement.
 * @return-failure Renvoie $Cfalse@ si une partie du travail a dû être faite par le thread principal.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see bunny_thread_wait_completion
 */
bool			bunny_list_fast_foreach(t_bunny_threadpool *pool,
						t_bunny_list	*list,
						void		(*func)
						(void		*nod,
						 void		*par),
						void		*par)
{
  t_bunny_node		*nod;
  int			err;

  for (nod = bunny_list_begin(list); nod != NULL; nod = bunny_list_next(nod))
    if (bunny_thread_push(pool, func, bunny_list_data(nod, void*), par) == false)
      {
	err = bunny_errno;
	while (nod != NULL)
	  {
	    func(bunny_list_data(nod, void*), par);
	    nod = bunny_list_next(nod);
	  }
	bunny_thread_wait_completion(pool);
	scream_error_if(return (false), err, PATTERN, "container", pool, list, func, par, "false");
      }
  bunny_thread_wait_completion(pool);
  scream_log_if(PATTERN, "container", pool, list, func, par, "true");
  return (true);
}
