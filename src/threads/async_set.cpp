// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<stdlib.h>
#include		"lapin_private.h"

static void		_free_threadpool(void)
{
  if (gl_bunny_loop_threadpool)
    {
      bunny_delete_threadpool(gl_bunny_loop_threadpool);
      gl_bunny_loop_threadpool = NULL;
    }
}

bool			bunny_set_async_computation(size_t	nbr)
{
  if (gl_bunny_loop_threadpool && gl_bunny_loop_threadpool->nbr_threads != nbr)
    {
      bunny_delete_threadpool(gl_bunny_loop_threadpool);
      gl_bunny_loop_threadpool = NULL;
    }
  if (nbr == 0)
    return (true);
  atexit(_free_threadpool);
  return ((bool)(gl_bunny_loop_threadpool = bunny_new_threadpool(nbr)));
}

