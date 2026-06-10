// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

struct			bunny_queue
{
  size_t		length;
  struct bunny_node	*front;
  struct bunny_node	*back;
};

struct			bunny_node
{
  void			*data;
  struct bunny_node	*next;
};

/*!
** Delete a queue and all of its internal nodes.
**
** Stored data pointers are not freed. Only the container nodes and the queue
** object itself are released.
**
** \param queue The queue to destroy.
** \return The number of elements that were stored in the queue.
*/
/**
 * @doc
 * @doc-symbol bunny_delete_queue
 * @doc-kind function
 * @doc-module queue
 * @doc-order 130
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a queue and its internal nodes.
 * @param queue The queue to delete.
 * @return-success Returns the number of elements that were in the queue.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see bunny_new_queue
 *
 * @doc-lang fr
 * @brief Détruit une file et ses nœuds internes.
 * @param queue La file à détruire.
 * @return-success Renvoie le nombre d'éléments qui étaient dans la file.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see bunny_new_queue
 */
size_t			bunny_delete_queue(t_bunny_queue	*queue)
{
  struct bunny_node	*nod = (struct bunny_node*)queue->front;
  struct bunny_node	*prv;
  size_t		siz = queue->length;

  while (nod)
    {
      prv = nod->next;
      bunny_free(nod);
      nod = prv;
    }
  bunny_free(queue);
  scream_log_if("%p -> %zu", "container", queue, siz);
  return (siz);
}

#define			PATTERN		"%p queue, %p data -> %s"

/*!
** Push a data pointer at the back of a queue.
**
** This is the typed implementation behind the bunny_queue_push macro.
**
** \param queue The queue to edit.
** \param data The data pointer to store.
** \return True on success, false on allocation error.
*/
bool			_bunny_queue_push(t_bunny_queue		*queue,
					  const void		*data)
{
  struct bunny_queue	*que = (struct bunny_queue*)queue;
  struct bunny_node	*nod = (struct bunny_node*)bunny_malloc(sizeof(*nod));

  if (nod == NULL)
    scream_error_if
      (return (false), bunny_errno, PATTERN, "container", queue, data, "false");

  nod->data = (void*)data;

  nod->next = NULL;
  if (que->front == NULL)
    que->front = nod;
  if (que->back != NULL)
    que->back->next = nod;
  que->back = nod;
  que->length += 1;
  scream_log_if(PATTERN, "container", queue, data, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

/*!
** Pop the data pointer stored at the front of a queue.
**
** The returned data is not freed by the container.
**
** \param queue The queue to edit.
** \return The extracted data pointer, or NULL if the queue is empty.
*/
void			*_bunny_queue_pop(t_bunny_queue		*queue)
{
  struct bunny_queue	*que = (struct bunny_queue*)queue;
  struct bunny_node	*nod;
  void			*dat;

  if ((nod = que->front) == NULL)
    scream_error_if
      (return (NULL), BE_CONTAINER_IS_EMPTY, PATTERN, "container", queue, nod);
  if ((que->front = nod->next) == NULL)
    que->back = NULL;
  dat = nod->data;
  bunny_free(nod);
  que->length -= 1;
  scream_log_if(PATTERN, "container", queue, dat);
  return (dat);
}

