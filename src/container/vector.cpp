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
  vec->original_nmemb = siz;
  vec->elemsize = siz;
  vec->array = &vec->data[0];
  vec->ctor = ctor;
  vec->dtor = dtor;
  if (ctor)
    for (i = 0; i < (int)bunny_vector_size(vec); ++i)
      if (ctor(bunny_vector_data(vec, i, void*), add) == false)
	{
	  if (dtor)
	    while (--i >= 0)
	      dtor(bunny_vector_data(vec, i, void*));
	  bunny_free(vec);
	  return (NULL);
	}
  scream_log_if(PATTERN, "container", nbr, siz, vec);
  return ((t_bunny_vector*)vec);
}

void			bunny_delete_vector(t_bunny_vector		*vec)
{
  int			i;

  if (vec->dtor)
    for (i = 0; i < (int)bunny_vector_size(vec); ++i)
      vec->dtor(bunny_vector_data(vec, i, void*));
  bunny_free(vec);
}

#undef			PATTERN
#define			PATTERN		"%p vector, %zu newsize -> %p"

t_bunny_vector		*bunny_vector_resize(t_bunny_vector		*vec,
					     size_t			newsize,
					     void			*add)
{
  struct bunny_vector	*old, *nw;
  int			i;

  if (newsize <= (old = (struct bunny_vector*)vec)->original_nmemb)
    {
      if (vec->dtor)
	for (i = bunny_vector_size(vec) - 1; i >= (int)newsize; --i)
	  vec->dtor(bunny_vector_data(vec, i, void*));
      old->nmemb = newsize;
      scream_log_if(PATTERN, "container", vec, newsize, vec);
      return (vec);
    }
  if ((nw = (struct bunny_vector*)bunny_realloc
       (old, sizeof(struct bunny_vector) + newsize * vec->elemsize)) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", vec, newsize, nw);
  nw->array = &nw->data[0];
  if (vec->ctor)
    for (i = nw->nmemb; i < (int)newsize; ++i)
      if (vec->ctor(bunny_vector_data(vec, i, void*), add) == false)
	{
	  if (vec->dtor)
	    while (--i >= (int)nw->nmemb)
	      vec->dtor(bunny_vector_data(vec, i, void*));
	  return ((t_bunny_vector*)nw);
	}
  nw->nmemb = newsize;
  nw->original_nmemb = newsize;
  scream_log_if(PATTERN, "container", vec, newsize, nw);
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
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", vec, nw);
  nw->array = &nw->data[0];
  scream_log_if(PATTERN, "container", vec, nw);
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

  return (pq->cmp(*(void**)a, *(void**)b, pq->ptr));
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
	  if (x < 0)
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
  qsort_r((void*)vec->array, vec->nmemb, vec->elemsize, to_qsort, &packet);
#endif
  scream_log_if("%p vector, %p cmp_func, %p param", "container", vec, cmp, param);
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
	scream_error_if
	  (return (false), err, PATTERN, "container", pool, vector, func, par, "false");
      }
  bunny_thread_wait_completion(pool);
  scream_log_if(PATTERN, "container", pool, vector, func, par, "true");
  return (true);
}
