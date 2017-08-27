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

#define			PATTERN		"%zu nmemb, %zu size -> %p"

t_bunny_vector		*_bunny_new_vector(size_t			nbr,
					   size_t			siz)
{
  struct bunny_vector	*vec;

  if ((vec = (struct bunny_vector*)bunny_malloc(sizeof(struct bunny_vector) + siz * nbr)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, nbr, siz, vec);
  vec->nmemb = nbr;
  vec->original_nmemb = siz;
  vec->elemsize = siz;
  vec->array = &vec->data[0];
  scream_log_if(PATTERN, nbr, siz, vec);
  return ((t_bunny_vector*)vec);
}

#undef			PATTERN
#define			PATTERN		"%p vector, %zu newsize -> %p"

t_bunny_vector		*bunny_vector_resize(t_bunny_vector		*vec,
					     size_t			newsize)
{
  struct bunny_vector	*old, *nw;

  if (newsize <= (old = (struct bunny_vector*)vec)->original_nmemb)
    {
      scream_log_if(PATTERN, vec, newsize, vec);
      return (vec);
    }
  if ((nw = (struct bunny_vector*)bunny_realloc
       (old, sizeof(struct bunny_vector) + newsize * vec->elemsize)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, vec, newsize, nw);
  nw->nmemb = newsize;
  nw->original_nmemb = newsize;
  nw->array = &nw->data[0];
  scream_log_if(PATTERN, vec, newsize, nw);
  return ((t_bunny_vector*)nw);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

t_bunny_vector		*bunny_vector_crop(t_bunny_vector		*vec)
{
  struct bunny_vector	*old, *nw;

  old = (struct bunny_vector*)vec;
  if ((nw = (struct bunny_vector*)bunny_realloc
       (old, sizeof(struct bunny_vector) + vec->nmemb * vec->elemsize)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, vec, nw);
  nw->array = &nw->data[0];
  scream_log_if(PATTERN, vec, nw);
  return ((t_bunny_vector*)nw);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

t_bunny_list		*bunny_vector_untie(const t_bunny_vector	*vec)
{
  t_bunny_list		*lst = bunny_new_list();
  t_bunny_node		*nod;
  void			*ptr;
  size_t		i;

  if (lst == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, vec, lst);
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

  scream_log_if(PATTERN, vec, lst);
  return (lst);

 erase_lst:
  for (nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod))
    bunny_free(bunny_list_data(nod, void*));
  bunny_delete_list(lst);
  scream_error_if(return (NULL), i, PATTERN, vec, lst);
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
  scream_log_if("%p vector, %p cmp_func, %p param", vec, cmp, param);
}

void			bunny_vector_foreach(t_bunny_vector	*vector,
					     t_bunny_vector_foreach func,
					     void		*param)
{
  size_t		i;

  for (i = 0; i < bunny_vector_size(vector); ++i)
    func(bunny_vector_data(vector, i, void*), param);
}

#undef			PATTERN
#define			PATTERN		"%p threadpool, %p vector, %p func, %p param -> %s"

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
    if (bunny_thread_push(pool, func, bunny_vector_data(vector, i, void*), par) == false)
      {
	err = bunny_errno;
	while (i < bunny_vector_size(vector))
	  {
	    func(bunny_vector_data(vector, i, void*), par);
	    ++i;
	  }
	bunny_thread_wait_completion(pool);
	scream_error_if(return (false), err, PATTERN, pool, vector, func, par, "false");
      }
  bunny_thread_wait_completion(pool);
  scream_log_if(PATTERN, pool, vector, func, par, "true");
  return (true);
}

