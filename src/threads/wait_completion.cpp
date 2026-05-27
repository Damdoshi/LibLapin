// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<list>
#include		"Threads.hpp"
#include		"lapin_private.h"

#ifndef			__WIN32

std::list<hbs::Work*>	_ToDelete;

void			_ClearWorkers(void)
{
  std::list<hbs::Work*>::iterator it;

  for (it = _ToDelete.begin(); it != _ToDelete.end(); ++it)
    delete *it;
  _ToDelete.clear();
}

/**
 * @doc
 * @doc-symbol bunny_thread_wait_completion
 * @doc-kind function
 * @doc-module threads
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Waits until a thread pool has completed all queued work.
 * @description bunny_thread_wait_completion blocks until every queued job is complete and no more work is waiting in the thread pool queue. It is useful between two foreach operations when their order matters.
 * @param pool The thread pool to wait on.
 * @log "thread"
 * @see bunny_thread_foreach
 * @see bunny_thread_push
 *
 * @doc-lang fr
 * @brief Attend qu'une réserve de threads ait terminé tous les travaux en attente.
 * @description bunny_thread_wait_completion bloque jusqu'à ce que chaque tâche en file soit terminée et qu'il n'y ait plus de travail en attente dans la réserve de threads. Elle est utile entre deux opérations foreach lorsque leur ordre est important.
 * @param pool La réserve de threads à attendre.
 * @log "thread"
 * @see bunny_thread_foreach
 * @see bunny_thread_push
 */

void			bunny_thread_wait_completion(t_bunny_threadpool	*pol)
{
  hbs::Workers		*w = (hbs::Workers*)pol->_private;
  hbs::Workers::Message	msg;

  while (w->GetHowManyTasks())
    bunny_usleep(300);
  while (w->GetMessage(msg));
  _ClearWorkers();
  scream_log_if("%p", "thread", pol);
}

#else

void			bunny_thread_wait_completion(t_bunny_threadpool	*pol)
{
  (void)pol;
  scream_log_if("%p", "thread", pol);
}

#endif


