// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<list>
#include		"Threads.hpp"
#include		"lapin_private.h"

#ifndef			__WIN32

class			_Launcher
  : public hbs::WorkSpec::Work3<_Launcher, t_bunny_function, void*, void*>
{
public:
  using hbs::WorkSpec::Work3<_Launcher, t_bunny_function, void*, void*>::operator();

  hbs::IdMessage	operator()(hbs::IdTask				task,
				   t_bunny_function			func,
				   void					*data,
				   void					*add)
  {
    (void)task;
    func(data, add);
    return (0);
  }

  _Launcher(t_bunny_function	func,
	    void		*data,
	    void		*add)
    : Work3(*this, func, data, add)
  {}
  ~_Launcher(void) {}
};

#endif

extern std::list<hbs::Work*>	_ToDelete;

#define			PATTERN						\
  "%p threadpool, %p function, %p data, %p additional data -> %s"

/**
 * @doc
 * @doc-symbol bunny_thread_push
 * @doc-kind function
 * @doc-module threads
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Pushes one job into a thread pool.
 * @description bunny_thread_push pushes a single work item into pool. A worker thread will call function with data as first parameter and add_ptr as second parameter.
 * @description On Windows, the function is called immediately and synchronously by the calling thread.
 * @param pool The thread pool that will execute the job.
 * @param function The function called to process data.
 * @param data The data to process asynchronously.
 * @param add_ptr An additional pointer transmitted as the second argument of function.
 * @return-case success On $Bsuccess@, returns $Ctrue@.
 * @return-case failure On $Bfailure@, returns $Cfalse@.
 * @error ENOMEM Out of memory.
 * @log "thread"
 * @see bunny_thread_foreach
 * @see bunny_thread_wait_completion
 *
 * @doc-lang fr
 * @brief Pousse une tâche dans une réserve de threads.
 * @description bunny_thread_push pousse un seul élément de travail dans pool. Un thread de travail appellera function avec data comme premier paramètre et add_ptr comme second paramètre.
 * @description Sur Windows, la fonction est appelée immédiatement et de manière synchrone par le thread appelant.
 * @param pool La réserve de threads qui exécutera la tâche.
 * @param function La fonction appelée pour traiter data.
 * @param data La donnée à traiter de manière asynchrone.
 * @param add_ptr Un pointeur additionnel transmis comme second argument de function.
 * @return-case success En cas de $Bsuccès@, renvoie $Ctrue@.
 * @return-case failure En cas d'$Béchec@, renvoie $Cfalse@.
 * @error ENOMEM Mémoire insuffisante.
 * @log "thread"
 * @see bunny_thread_foreach
 * @see bunny_thread_wait_completion
 */

bool			bunny_thread_push(t_bunny_threadpool		*pol,
					  t_bunny_function		func,
					  void				*data,
					  void				*param)
{
#ifndef			__WIN32
  hbs::Workers		*workers = (hbs::Workers*)pol->_private;
  hbs::Work		*work;

  if ((work = new (std::nothrow) _Launcher(func, data, param)) == NULL)
    scream_error_if(return (false), ENOMEM, PATTERN, "thread", pol, func, data, param, "false");
  try
    {
      _ToDelete.push_back(work);
    }
  catch (...)
    {
      delete work;
      scream_error_if(return (false), ENOMEM, PATTERN, "thread", pol, func, data, param, "false");
    }
  if (workers->Add(*work) == false)
    {
      _ToDelete.pop_back();
      delete work;
      scream_error_if(return (false), bunny_errno, PATTERN, "thread", pol, func, data, param, "false");
      return (false);
    }
  scream_log_if(PATTERN, "thread", pol, func, data, param, "true");
  return (true);
#else
  (void)pol;
  func(data, param);
  scream_log_if(PATTERN, "thread", pol, func, data, param, "true");
  return (true);
#endif
}

