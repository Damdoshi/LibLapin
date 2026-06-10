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

/**
 * @doc
 * @doc-symbol bunny_set_async_computation
 * @doc-kind function
 * @doc-module threads
 * @doc-order 230
 * @doc-since 12
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Creates or destroys the thread pool used by bunny_loop asynchronous computations.
 * @description bunny_set_async_computation defines how many threads will work behind bunny_loop to run jobs pushed by bunny_async_computation_push and bunny_async_computation_foreach.
 * @description If an asynchronous computation thread pool already exists with a different number of threads, it is destroyed before the new one is created. Passing 0 only destroys the existing pool. A pool created by this function is automatically freed at program exit if it was not freed earlier.
 * @param nbr_threads The number of threads inside the bunny_loop thread pool. Send 0 to delete it without creating a new one.
 * @return-case success On $Bsuccess@, returns $Ctrue@. Sending 0 is considered a success.
 * @return-case failure On $Bfailure@, returns $Cfalse@.
 * @error ENOMEM Out of memory.
 * @see bunny_async_computation_push
 * @see bunny_async_computation_foreach
 *
 * @doc-lang fr
 * @brief Crée ou détruit la réserve de threads utilisée par les calculs asynchrones de bunny_loop.
 * @description bunny_set_async_computation définit combien de threads travailleront derrière bunny_loop pour exécuter les tâches poussées par bunny_async_computation_push et bunny_async_computation_foreach.
 * @description Si une réserve de threads de calcul asynchrone existe déjà avec un nombre de threads différent, elle est détruite avant la création de la nouvelle. Envoyer 0 détruit seulement la réserve existante. Une réserve créée par cette fonction est automatiquement libérée à la fin du programme si elle n'a pas été libérée avant.
 * @param nbr_threads Le nombre de threads dans la réserve de bunny_loop. Envoyez 0 pour la supprimer sans en créer une nouvelle.
 * @return-case success En cas de $Bsuccès@, renvoie $Ctrue@. Envoyer 0 est considéré comme un succès.
 * @return-case failure En cas d'$Béchec@, renvoie $Cfalse@.
 * @error ENOMEM Mémoire insuffisante.
 * @see bunny_async_computation_push
 * @see bunny_async_computation_foreach
 */

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

