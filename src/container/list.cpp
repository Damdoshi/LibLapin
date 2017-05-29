// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		<stdlib.h>
#include		<alloca.h>
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
  return (siz);
}

bool			_bunny_list_push_front(t_bunny_list	*list,
					       const void	*data)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod = (struct bunny_node*)bunny_malloc(sizeof(*nod));

  if (nod == NULL)
    return (false);
  nod->prev = NULL;
  nod->next = lst->front;
  if (lst->front != NULL)
    lst->front->prev = nod;
  lst->front = nod;
  if (lst->back == NULL)
    lst->back = nod;
  nod->data = (void*)data;
  lst->length += 1;
  return (true);
}

bool			_bunny_list_push_back(t_bunny_list	*list,
					      const void	*data)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod = (struct bunny_node*)bunny_malloc(sizeof(*nod));

  if (nod == NULL)
    return (false);
  nod->next = NULL;
  nod->prev = lst->back;
  if (lst->back != NULL)
    lst->back->next = nod;
  lst->back = nod;
  if (lst->front == NULL)
    lst->front = nod;
  nod->data = (void*)data;
  lst->length += 1;
  return (true);
}

void			*_bunny_list_pop_front(t_bunny_list	*list)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod;
  void			*dat;

  if ((nod = lst->front) == NULL)
    return (NULL);
  if ((lst->front = nod->next) != NULL)
    lst->front->prev = NULL;
  else
    lst->back = NULL;
  dat = nod->data;
  bunny_free(nod);
  lst->length -= 1;
  return (dat);
}

void			*_bunny_list_pop_back(t_bunny_list	*list)
{
  struct bunny_list	*lst = (struct bunny_list*)list;
  struct bunny_node	*nod;
  void			*dat;

  if ((nod = lst->back) == NULL)
    return (NULL);
  if ((lst->back = nod->prev) != NULL)
    lst->back->next = NULL;
  else
    lst->front = NULL;
  dat = nod->data;
  bunny_free(nod);
  lst->length -= 1;
  return (dat);
}

t_bunny_list		*bunny_list_filter(t_bunny_list		*list,
					   bool			(*filter)(const void	*lst,
									  void		*param),
					   void			*param)
{
  t_bunny_list		*lst = bunny_new_list();
  t_bunny_node		*node;

  if (lst == NULL)
    return (NULL);
  for (node = bunny_list_begin(list); node != NULL; node = bunny_list_next(node))
    if (filter(node->data, param))
      if (bunny_list_push_back(lst, node->data) == false)
	{
	  bunny_delete_list(lst);
	  return (NULL);
	}
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

void			bunny_list_sort(t_bunny_list		*list,
					int			(*cmp)(const void	*a,
								       const void	*b,
								       void		*param),
					void			*param)
{
  struct qsort_packet	packet;
  void			**array = (void**)alloca(bunny_list_size(list) * sizeof(*array));
  t_bunny_node		*node;
  size_t		i;

  for (node = bunny_list_begin(list), i = 0; node != NULL; node = bunny_list_next(node), ++i)
    array[i] = (void*)node->data;
  packet.cmp = cmp;
  packet.ptr = param;
  qsort_r(&array[0], bunny_list_size(list), sizeof(*array), to_qsort, &packet);
  for (node = bunny_list_begin(list), i = 0; node != NULL; node = bunny_list_next(node), ++i)
    node->data = (void*)array[i];
}

t_bunny_vector		*_bunny_list_tie(const t_bunny_list	*lst,
					 size_t			elemsize)
{
  t_bunny_vector	*vec;
  t_bunny_node		*nod;
  size_t		i;

  if ((vec = bunny_new_vector(bunny_list_size(lst), elemsize)) == NULL)
    return (NULL);
  for (nod = bunny_list_begin(lst), i = 0; nod != NULL; nod = bunny_list_next(nod), ++i)
    memcpy(bunny_vector_address(vec, i), &bunny_list_data(nod, void*), elemsize);
  return (vec);
}

bool			bunny_list_fast_foreach(t_bunny_threadpool *pool,
						t_bunny_list	*list,
						void		(*func)
						(void		*nod,
						 const void	*par),
						 const void	*par)
{
  t_bunny_node		*nod;

  for (nod = bunny_list_begin(list); nod != NULL; nod = bunny_list_next(nod))
    if (bunny_thread_push(pool, func, bunny_list_data(nod, void*), par) == false)
      {
	while (nod != NULL)
	  {
	    func(bunny_list_data(nod, void*), par);
	    nod = bunny_list_next(nod);
	  }
	return (false);
      }
  return (true);
}

