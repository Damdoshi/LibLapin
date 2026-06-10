// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"Threads.hpp"
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_delete_threadpool
 * @doc-kind function
 * @doc-module threads
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Deletes a thread pool.
 * @description bunny_delete_threadpool destroys the thread pool and stops its worker threads before returning. The pool pointer must have been returned by bunny_new_threadpool.
 * @param pool The thread pool to destroy.
 * @log "thread"
 * @see bunny_new_threadpool
 * @see bunny_thread_wait_completion
 *
 * @doc-lang fr
 * @brief Détruit une réserve de threads.
 * @description bunny_delete_threadpool détruit la réserve de threads et arrête ses threads de travail avant de retourner. Le pointeur pool doit provenir de bunny_new_threadpool.
 * @param pool La réserve de threads à détruire.
 * @log "thread"
 * @see bunny_new_threadpool
 * @see bunny_thread_wait_completion
 */

void			bunny_delete_threadpool(t_bunny_threadpool		*pol)
{
#ifndef         __WIN32
  delete (hbs::Workers*)pol->_private;
#endif
  bunny_free(pol);
  scream_log_if("%p", "thread", pol);
}

