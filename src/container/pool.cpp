// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

struct			bunny_pool
{
  size_t		nmemb;
  size_t		elemsize;
  size_t		nbr_occupied;
  void			*array[0];
  // Followed by nmemb ptr
  // Followed by nmemb * elemsize bytes
};

#define			PATTERN		"%zu nmemb, %zu size -> %p"

t_bunny_pool		*_bunny_new_pool(size_t			nmemb,
					 size_t			size)
{
  struct bunny_pool	*pol;
  char			*ptr;
  size_t		i;

  size += sizeof(size_t);
  size += size % sizeof(size_t); // Allignment
  if ((pol = (struct bunny_pool*)bunny_malloc
       (i = sizeof(struct bunny_pool)
	+ size * nmemb
	+ nmemb * sizeof(pol->array[0]))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, nmemb, size, (void*)NULL);
  memset(pol, 0, i);
  pol->nmemb = nmemb;
  pol->elemsize = size;
  pol->nbr_occupied = 0;
  for (ptr = (char*)&pol->array[nmemb], i = 0; i < nmemb; ++i, ptr = &ptr[size])
    {
      *((size_t*)ptr) = i;
      pol->array[i] = (void*)&((size_t*)ptr)[1];
    }
  scream_log_if(PATTERN, nmemb, size, pol);
  return ((t_bunny_pool*)pol);
}

void			*bunny_pool_getv(t_bunny_pool		*pol,
					 size_t			*id)
{
  struct bunny_pool	*pool = (struct bunny_pool*)pol;
  size_t		*ret;

  if (pool->nbr_occupied >= pool->nmemb)
    return (NULL);
  ret = (size_t*)pool->array[pool->nbr_occupied++];
  if (id)
    *id = ret[-1];
  return (ret);
}

void			bunny_pool_free(t_bunny_pool		*pol,
					void			*elem)
{
  struct bunny_pool	*pool = (struct bunny_pool*)pol;
  size_t		*e = &(((size_t*)elem)[-1]);

  if (pool->nbr_occupied == 0)
    return ;
  pool->nbr_occupied -= 1;
  bunny_swap(&pool->array[*e], &pool->array[pool->nbr_occupied]);

  ((size_t*)pool->array[*e])[-1] = *e;
  ((size_t*)pool->array[pool->nbr_occupied])[-1] = pool->nbr_occupied;
}

void			bunny_pool_foreach(t_bunny_pool		*pool,
					   t_bunny_pool_foreach	func,
					   void			*param)
{
  size_t		i;

  for (i = 0; i < bunny_pool_size(pool); ++i)
    func(pool->data[i], param);
}

#undef			PATTERN
#define			PATTERN		"%p threadpool, %p pool, %p func, %p par -> %s"

bool			bunny_pool_fast_foreach(t_bunny_threadpool *the,
						t_bunny_pool	*pool,
						void		(*func)
						(void		*nod,
						 void		*par),
						void		*par)
{
  size_t		i;
  int			err;

  for (i = 0; i < bunny_pool_occupied_elem(pool); ++i)
    if (bunny_thread_push(the, func, (void*)pool->data[i], par) == false)
      {
	err = bunny_errno;
	while (i < bunny_pool_occupied_elem(pool))
	  {
	    func(&((size_t*)pool->data[i])[1], par);
	    ++i;
	  }
	bunny_thread_wait_completion(the);
	scream_error_if(return (false), err, PATTERN, the, pool, func, par, "false");
      }
  bunny_thread_wait_completion(the);
  scream_log_if(PATTERN, the, pool, func, par, "true");
  return (true);
}

