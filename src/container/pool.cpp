// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

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

  if ((pol = (struct bunny_pool*)bunny_malloc
       (sizeof(struct bunny_pool) + size * nmemb + size * sizeof(pol->array[0]))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, nmemb, size, (void*)NULL);
  pol->nmemb = nmemb;
  pol->elemsize = size;
  pol->nbr_occupied = 0;
  for (ptr = (char*)&pol->array[nmemb], i = 0; i < nmemb; ++i, ptr = &ptr[size])
    pol->array[i] = ptr;
  scream_log_if(PATTERN, nmemb, size, pol);
  return ((t_bunny_pool*)pol);
}

#undef			PATTERN
#define			PATTERN		"%p threadpool, %p pool, %p func, %p par -> %s"

bool			bunny_pool_fast_foreach(t_bunny_threadpool *the,
						t_bunny_pool	*pool,
						void		(*func)
						(void		*nod,
						 const void	*par),
						const void	*par)
{
  size_t		i;
  int			err;

  for (i = 0; i < bunny_pool_occupied_elem(pool); ++i)
    if (bunny_thread_push(the, func, (void*)pool->array[i], par) == false)
      {
	err = bunny_errno;
	while (i < bunny_pool_occupied_elem(pool))
	  {
	    func((void*)pool->array[i], par);
	    ++i;
	  }
	scream_error_if(return (false), err, PATTERN, the, pool, func, par, "false");
      }
  scream_log_if(PATTERN, the, pool, func, par, "true");
  return (true);
}

