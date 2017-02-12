// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"Threads.hpp"
#include		"lapin.h"

struct			bunny_threadpool
{
#ifndef         __WIN32
  hbs::Workers		*workers;
#else
  void          *workers; // currently no threads on Windows.
#endif
  size_t		nbr_threads;
};

t_bunny_threadpool	*bunny_new_threadpool(size_t		nbr)
{
  struct bunny_threadpool	*x;

  if ((x = (struct bunny_threadpool*)bunny_malloc(sizeof(*x))) == NULL)
    return (NULL);
#ifndef         __WIN32
  try
    {
      x->workers = new hbs::Workers(nbr);
    }
  catch (const std::bad_alloc &e)
    {
      bunny_free(x);
      return (NULL);
    }
#else
    x->workers = NULL;
#endif // __WIN32
  x->nbr_threads = nbr;
  return ((t_bunny_threadpool*)x);
}

