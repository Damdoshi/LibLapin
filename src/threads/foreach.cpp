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

extern std::list<hbs::Work*>	_ToDelete;

void			_ClearWorkers(void);

#endif

#define			PATTERN						\
  "%p threadpool, %p function, %p data array, %zu array len, %p additional data -> %s"

/**
 * @doc
 * @doc-symbol bunny_thread_foreach
 * @doc-kind function
 * @doc-module threads
 * @doc-order 210
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Splits an array computation into thread pool jobs.
 * @description bunny_thread_foreach pushes one job for each element of data. Each job calls function with one element of data as first parameter and add_ptr as second parameter.
 * @description The calling thread does not wait for the jobs to finish. Call bunny_thread_wait_completion when you need to wait before starting dependent work.
 * @description On Windows, all jobs are executed immediately and synchronously by the calling thread.
 * @param pool The thread pool that will execute the jobs.
 * @param function The function called for each element of data.
 * @param data An array of pointers. Each element is sent as the first argument of function.
 * @param data_array_len The number of elements in data.
 * @param add_ptr An additional pointer transmitted as the second argument of function.
 * @return-case success On $Bsuccess@, returns $Ctrue@.
 * @return-case failure On $Bfailure@, returns $Cfalse@.
 * @error ENOMEM Out of memory.
 * @log "thread"
 * @see bunny_thread_push
 * @see bunny_thread_wait_completion
 *
 * @doc-lang fr
 * @brief Découpe un calcul sur tableau en tâches pour une réserve de threads.
 * @description bunny_thread_foreach pousse une tâche pour chaque élément de data. Chaque tâche appelle function avec un élément de data comme premier paramètre et add_ptr comme second paramètre.
 * @description Le thread appelant n'attend pas la fin des tâches. Appelez bunny_thread_wait_completion lorsque vous devez attendre avant de lancer un travail dépendant.
 * @description Sur Windows, toutes les tâches sont exécutées immédiatement et de manière synchrone par le thread appelant.
 * @param pool La réserve de threads qui exécutera les tâches.
 * @param function La fonction appelée pour chaque élément de data.
 * @param data Un tableau de pointeurs. Chaque élément est envoyé comme premier argument de function.
 * @param data_array_len Le nombre d'éléments dans data.
 * @param add_ptr Un pointeur additionnel transmis comme second argument de function.
 * @return-case success En cas de $Bsuccès@, renvoie $Ctrue@.
 * @return-case failure En cas d'$Béchec@, renvoie $Cfalse@.
 * @error ENOMEM Mémoire insuffisante.
 * @log "thread"
 * @see bunny_thread_push
 * @see bunny_thread_wait_completion
 */

bool			bunny_thread_foreach(t_bunny_threadpool		*pol,
					     t_bunny_function		func,
					     void			**data,
					     size_t			len,
					     void			*add_ptr)
{
#ifndef			__WIN32
  hbs::Workers		*work = (hbs::Workers*)pol->_private;
  std::list<hbs::Workers::Task> task;
  size_t		i;

  for (i = 0; i < len; ++i)
    {
      _Launcher		*ptr;

      if ((ptr = new (std::nothrow) _Launcher(func, data[i], add_ptr)) == NULL)
	{
	  _ClearWorkers();
	  scream_error_if(return (false), ENOMEM, PATTERN, "thread", pol, func, data, len, add_ptr, "false");
	}
      try
	{
	  _ToDelete.push_back(ptr);
	  task.push_back(hbs::Workers::Task(ptr, i));
	}
      catch (...)
	{
	  _ClearWorkers();
	  scream_error_if(return (false), ENOMEM, PATTERN, "thread", pol, func, data, len, add_ptr, "false");
	}
    }
  if (work->Add(task) == false)
    {
      _ClearWorkers();
      scream_error_if(return (false), bunny_errno, PATTERN, "thread", pol, func, data, len, add_ptr, "false");
    }
  scream_log_if(PATTERN, "thread", pol, func, data, len, add_ptr, "true");
  return (true);

#else
  size_t		i;

  (void)pol;
  for (i = 0; i < len; ++i)
    func(data[i], add_ptr);
  scream_log_if(PATTERN, "thread", pol, func, data, len, add_ptr, "true");
  return (true);
#endif
}

