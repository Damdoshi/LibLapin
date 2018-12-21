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
  if (que->back == NULL)
    que->back = nod;
  else
    {
      que->back->next = nod;
      que->back = nod;
    }
  que->length += 1;
  scream_log_if(PATTERN, "container", queue, data, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

void			*_bunny_queue_pop(t_bunny_queue		*queue)
{
  struct bunny_queue	*que = (struct bunny_queue*)queue;
  struct bunny_node	*nod;
  void			*dat;

  if ((nod = que->front) == NULL)
    scream_error_if
      (return (NULL), BE_CONTAINER_IS_EMPTY, PATTERN, "container", queue, nod);
  que->front = nod->next;
  dat = nod->data;
  bunny_free(nod);
  que->length -= 1;
  scream_log_if(PATTERN, "container", queue, dat);
  return (dat);
}

