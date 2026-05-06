// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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

/**
 * @doc
 * @doc-symbol bunny_new_threadpool
 * @doc-kind function
 * @doc-module threads
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Creates a thread pool.
 * @description bunny_new_threadpool creates nbr_threads worker threads and returns a thread pool handle representing them. The returned thread pool must be destroyed with bunny_delete_threadpool.
 * @description On Windows, the handle is still created but pushed jobs are executed synchronously by the calling thread.
 * @param nbr_threads The number of worker threads to create.
 * @return-case success On $Bsuccess@, returns the created thread pool.
 * @return-case failure On $Bfailure@, returns $CNULL@.
 * @error ENOMEM Out of memory.
 * @log "thread"
 * @see t_bunny_threadpool
 * @see bunny_delete_threadpool
 *
 * @doc-lang fr
 * @brief Crée une réserve de threads.
 * @description bunny_new_threadpool crée nbr_threads threads de travail et renvoie un handle représentant cette réserve de threads. La réserve renvoyée doit être détruite avec bunny_delete_threadpool.
 * @description Sur Windows, le handle est tout de même créé mais les tâches poussées sont exécutées de manière synchrone par le thread appelant.
 * @param nbr_threads Le nombre de threads de travail à créer.
 * @return-case success En cas de $Bsuccès@, renvoie la réserve de threads créée.
 * @return-case failure En cas d'$Béchec@, renvoie $CNULL@.
 * @error ENOMEM Mémoire insuffisante.
 * @log "thread"
 * @see t_bunny_threadpool
 * @see bunny_delete_threadpool
 */

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

