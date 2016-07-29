// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"Threads.hpp"
#include		"lapin.h"

struct			bunny_threadpool
{
  hbs::Workers		*workers;
  size_t		nbr_threads;
};

t_bunny_threadpool	*bunny_new_threadpool(size_t		nbr)
{
  struct bunny_threadpool	*x;

  if ((x = (struct bunny_threadpool*)bunny_malloc(sizeof(*x))) == NULL)
    return (NULL);
  if ((x->workers = new (std::nothrow) hbs::Workers(nbr)) == NULL)
    {
      bunny_free(x);
      return (NULL);
    }
  x->nbr_threads = nbr;
  return ((t_bunny_threadpool*)x);
}

