// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"Threads.hpp"
#include		"lapin_private.h"

struct			bunny_threadpool
{
#ifndef         __WIN32
  hbs::Workers		*workers;
#else
  void			*workers; // currently no threads on Windows.
#endif
  size_t		nbr_threads;
};

#define			PATTERN		"%zu -> %p"

t_bunny_threadpool	*bunny_new_threadpool(size_t		nbr)
{
  struct bunny_threadpool	*x;

  if ((x = (struct bunny_threadpool*)bunny_malloc(sizeof(*x))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "thread", nbr, (void*)NULL);
#ifndef         __WIN32
  try
    {
      x->workers = new hbs::Workers(nbr);
    }
  catch (const std::bad_alloc &e)
    {
      bunny_free(x);
      scream_error_if(return (NULL), ENOMEM, PATTERN, "thread", nbr, (void*)NULL);
    }
#else
  x->workers = NULL;
#endif // __WIN32
  x->nbr_threads = nbr;
  scream_log_if(PATTERN, "thread", nbr, x);
  return ((t_bunny_threadpool*)x);
}

