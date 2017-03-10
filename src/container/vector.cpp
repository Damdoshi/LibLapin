// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		"lapin_private.h"

struct			bunny_vector
{
  size_t		nmemb;
  size_t		elemsize;
  void			*array;
  /* private */
  size_t		original_nmemb;
  char			data[0];
};

t_bunny_vector		*_bunny_new_vector(size_t			nbr,
					   size_t			siz)
{
  struct bunny_vector	*vec;

  if ((vec = (struct bunny_vector*)bunny_malloc(sizeof(struct bunny_vector) + siz * nbr)) == NULL)
    return (NULL);
  vec->nmemb = nbr;
  vec->original_nmemb = siz;
  vec->elemsize = siz;
  vec->array = &vec->data[0];
  return ((t_bunny_vector*)vec);
}

t_bunny_vector		*bunny_vector_resize(t_bunny_vector		*vec,
					     size_t			newsize)
{
  struct bunny_vector	*old, *nw;

  if (newsize <= (old = (struct bunny_vector*)vec)->original_nmemb)
    return (vec);
  if ((nw = (struct bunny_vector*)bunny_realloc
       (old, sizeof(struct bunny_vector) + newsize * vec->elemsize)) == NULL)
    return (NULL);
  nw->nmemb = newsize;
  nw->original_nmemb = newsize;
  nw->array = &nw->data[0];
  return ((t_bunny_vector*)nw);
}

t_bunny_vector		*bunny_vector_crop(t_bunny_vector		*vec)
{
  struct bunny_vector	*old, *nw;

  old = (struct bunny_vector*)vec;
  if ((nw = (struct bunny_vector*)bunny_realloc
       (old, sizeof(struct bunny_vector) + vec->nmemb * vec->elemsize)) == NULL)
    return (NULL);
  nw->array = &nw->data[0];
  return ((t_bunny_vector*)nw);
}

t_bunny_list		*bunny_vector_untie(const t_bunny_vector	*vec)
{
  t_bunny_list		*lst = bunny_new_list();
  t_bunny_node		*nod;
  void			*ptr;
  size_t		i;

  if (lst == NULL)
    return (NULL);
  for (i = 0; i < bunny_vector_size(vec); ++i)
    {
      if ((ptr = bunny_memdup(bunny_vector_address(vec, i), bunny_vector_elem_size(vec))) == NULL)
	goto erase_lst;
      if (bunny_list_push_back(lst, ptr) == false)
	{
	  bunny_free(ptr);
	  goto erase_lst;
	}
    }

  return (lst);
 erase_lst:
  for (nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod))
    bunny_free(bunny_list_data(nod, void*));
  bunny_delete_list(lst);
  return (NULL);
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

void			bunny_vector_sort(t_bunny_vector		*vec,
					  t_bunny_comparator		cmp,
					  void				*param)
{
  struct qsort_packet	packet;

  packet.cmp = cmp;
  packet.ptr = param;
  qsort_r((void*)vec->array, vec->nmemb, vec->elemsize, to_qsort, &packet);
}

bool			bunny_vector_fast_foreach(t_bunny_threadpool *pool,
						  t_bunny_vector *vector,
						  void		(*func)
						  (void		*nod,
						   const void	*par),
						  const void	*par)
{
  size_t		i;

  for (i = 0; i < bunny_vector_size(vector); ++i)
    if (bunny_thread_push(pool, func, bunny_vector_data(vector, i, void*), par) == false)
      {
	while (i < bunny_vector_size(vector))
	  {
	    func(bunny_vector_data(vector, i, void*), par);
	    ++i;
	  }
	return (false);
      }
  return (true);
}

