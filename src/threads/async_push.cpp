// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			async_wrap(void					*data,
				   void					*add)
{
  t_async_order		*ord = (t_async_order*)data;

  (void)add;
  ord->func(ord->data_to_compute, ord->add_ptr);
  if (gl_callback.async_computation)
    gl_completed_tasks.push(ord->data_to_compute);
}

/**
 * @doc
 * @doc-symbol bunny_async_computation_push
 * @doc-kind function
 * @doc-module threads
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Pushes one computation into the bunny_loop thread pool.
 * @description bunny_async_computation_push pushes one computation request into the thread pool configured by bunny_set_async_computation. The function callback receives data as first parameter and the current bunny loop data as second parameter. A thread pool must have been created with bunny_set_async_computation before calling this function.
 * @description When the computation is complete, the async computation event can be triggered if a callback was registered for it.
 * @param function The function to call for the computation.
 * @param data The data to compute.
 * @return-case success On $Bsuccess@, returns $Ctrue@.
 * @return-case failure On $Bfailure@, returns $Cfalse@.
 * @error ENOMEM Out of memory.
 * @see bunny_set_async_computation
 * @see bunny_async_computation_foreach
 *
 * @doc-lang fr
 * @brief Pousse un calcul dans la réserve de threads de bunny_loop.
 * @description bunny_async_computation_push pousse une demande de calcul dans la réserve de threads configurée par bunny_set_async_computation. Le callback function reçoit data comme premier paramètre et les données courantes de la boucle bunny comme second paramètre. Une réserve de threads doit avoir été créée avec bunny_set_async_computation avant d'appeler cette fonction.
 * @description Lorsque le calcul est terminé, l'événement de calcul asynchrone peut être déclenché si un callback a été enregistré pour lui.
 * @param function La fonction à appeler pour le calcul.
 * @param data La donnée à calculer.
 * @return-case success En cas de $Bsuccès@, renvoie $Ctrue@.
 * @return-case failure En cas d'$Béchec@, renvoie $Cfalse@.
 * @error ENOMEM Mémoire insuffisante.
 * @see bunny_set_async_computation
 * @see bunny_async_computation_foreach
 */

bool			bunny_async_computation_push(t_bunny_function	func,
						     void		*dt)
{
  t_async_order		*ord;

  if ((ord = (t_async_order*)bunny_malloc(sizeof(*ord))) == NULL)
    return (false);
  ord->func = func;
  ord->data_to_compute = dt;
  ord->add_ptr = gl_loop_data;
  return (bunny_thread_push(gl_bunny_loop_threadpool, async_wrap, ord, NULL));
}

