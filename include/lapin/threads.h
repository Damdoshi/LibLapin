/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/**
 * @doc
 * @doc-symbol threads
 * @doc-kind module
 * @doc-module threads
 * @doc-order 0
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Shares computations between several worker threads.
 * @description The threads module is an easy-to-use thread pool system. It allows a program to exploit several processor threads without exposing the user to low-level thread management, by pushing individual jobs or foreach-like computations into a pool.
 * @description On Windows, this module currently keeps the same API but executes pushed jobs synchronously instead of using real worker threads.
 * @header lapin/threads.h
 *
 * @doc-lang fr
 * @brief Répartit des calculs entre plusieurs threads de travail.
 * @description Le module threads est un système simple de réserve de threads. Il permet à un programme d'exploiter plusieurs threads processeur sans exposer l'utilisateur à la gestion bas niveau des threads, en poussant des tâches individuelles ou des calculs de type foreach dans une réserve.
 * @description Sur Windows, ce module conserve actuellement la même API mais exécute les tâches poussées de manière synchrone au lieu d'utiliser de vrais threads de travail.
 * @header lapin/threads.h
 */

#ifndef				__LAPIN_THREADS_H__
# define			__LAPIN_THREADS_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/**
 * @doc
 * @doc-symbol t_bunny_threadpool
 * @doc-kind struct
 * @doc-module threads
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Represents a LibLapin thread pool.
 * @description t_bunny_threadpool is an abstract public handle used to represent a group of worker threads created by bunny_new_threadpool. Its private field must not be accessed by user code.
 * @field _private Private implementation pointer. Do not modify it.
 * @field nbr_threads The number of threads represented by this thread pool.
 * @see bunny_new_threadpool
 * @see bunny_delete_threadpool
 *
 * @doc-lang fr
 * @brief Représente une réserve de threads de la LibLapin.
 * @description t_bunny_threadpool est un handle public abstrait utilisé pour représenter un groupe de threads de travail créé par bunny_new_threadpool. Son champ privé ne doit pas être manipulé par le code utilisateur.
 * @field _private Pointeur d'implémentation privé. Ne le modifiez pas.
 * @field nbr_threads Le nombre de threads représentés par cette réserve de threads.
 * @see bunny_new_threadpool
 * @see bunny_delete_threadpool
 */
typedef struct			s_bunny_threadpool
{
  const void * const		_private;
  size_t			nbr_threads;
}				t_bunny_threadpool;

t_bunny_threadpool		*bunny_new_threadpool(size_t			nbr_threads);

void				bunny_delete_threadpool(t_bunny_threadpool	*pool);

/**
 * @doc
 * @doc-symbol t_bunny_function
 * @doc-kind callback
 * @doc-module threads
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Callback type executed by thread jobs.
 * @description t_bunny_function is the function pointer type used by bunny_thread_push, bunny_thread_foreach and the asynchronous computation helpers. The first argument is the item to process. The second argument is an additional pointer shared by all calls of a same operation.
 * @param data The data item to process. In foreach operations, this value comes from the data array.
 * @param add_ptr An additional pointer transmitted to the callback. It may be shared by several worker threads, so take care of race conditions and preferably use it as read-only shared data.
 * @see bunny_thread_push
 * @see bunny_thread_foreach
 *
 * @doc-lang fr
 * @brief Type de callback exécuté par les tâches des threads.
 * @description t_bunny_function est le type de pointeur de fonction utilisé par bunny_thread_push, bunny_thread_foreach et les assistants de calcul asynchrone. Le premier argument est l'élément à traiter. Le second argument est un pointeur additionnel partagé par tous les appels d'une même opération.
 * @param data L'élément à traiter. Dans les opérations foreach, cette valeur provient du tableau de données.
 * @param add_ptr Un pointeur additionnel transmis au callback. Il peut être partagé par plusieurs threads de travail, faites donc attention aux conditions de course et utilisez-le de préférence comme donnée partagée en lecture seule.
 * @see bunny_thread_push
 * @see bunny_thread_foreach
 */
typedef void			(*t_bunny_function)(void			*data,
					    void			*add_ptr);

bool				bunny_thread_foreach(t_bunny_threadpool		*pool,
					     t_bunny_function		function,
					     void			**data,
					     size_t			data_array_len,
					     void			*add_ptr);

bool				bunny_thread_push(t_bunny_threadpool		*pool,
					  t_bunny_function		function,
					  void				*data,
					  void				*add_ptr);

void				bunny_thread_wait_completion(t_bunny_threadpool	*pool);

bool				bunny_set_async_computation(size_t		nbr_threads);

bool				bunny_async_computation_push(t_bunny_function	function,
						     void		*data);

bool				bunny_async_computation_foreach(t_bunny_function function,
							void		**data,
							size_t		data_array_len);

#endif	/*			__LAPIN_THREADS_H__	*/
