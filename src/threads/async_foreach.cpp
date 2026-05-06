// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_async_computation_foreach
 * @doc-kind function
 * @doc-module threads
 * @doc-order 250
 * @doc-since 12
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Pushes several computations into the bunny_loop thread pool.
 * @description bunny_async_computation_foreach pushes one asynchronous computation request for each element of data. Each request calls function with one element of data as first parameter and the current bunny loop data as second parameter. A thread pool must have been created with bunny_set_async_computation before calling this function.
 * @description Elements successfully pushed are replaced with NULL in the data array. The function still tries to push following elements after a failure and reports whether every push succeeded.
 * @param function The function to call for each computation.
 * @param data An array containing every data pointer to compute.
 * @param data_array_len The number of elements in data.
 * @return-case success On $Bsuccess@, returns $Ctrue@ if every computation request was pushed.
 * @return-case failure On $Bfailure@, returns $Cfalse@ if at least one computation request could not be pushed.
 * @error ENOMEM Out of memory.
 * @see bunny_set_async_computation
 * @see bunny_async_computation_push
 *
 * @doc-lang fr
 * @brief Pousse plusieurs calculs dans la réserve de threads de bunny_loop.
 * @description bunny_async_computation_foreach pousse une demande de calcul asynchrone pour chaque élément de data. Chaque demande appelle function avec un élément de data comme premier paramètre et les données courantes de la boucle bunny comme second paramètre. Une réserve de threads doit avoir été créée avec bunny_set_async_computation avant d'appeler cette fonction.
 * @description Les éléments poussés avec succès sont remplacés par NULL dans le tableau data. La fonction continue d'essayer de pousser les éléments suivants après un échec et indique si toutes les demandes ont réussi.
 * @param function La fonction à appeler pour chaque calcul.
 * @param data Un tableau contenant tous les pointeurs de données à calculer.
 * @param data_array_len Le nombre d'éléments dans data.
 * @return-case success En cas de $Bsuccès@, renvoie $Ctrue@ si toutes les demandes de calcul ont été poussées.
 * @return-case failure En cas d'$Béchec@, renvoie $Cfalse@ si au moins une demande de calcul n'a pas pu être poussée.
 * @error ENOMEM Mémoire insuffisante.
 * @see bunny_set_async_computation
 * @see bunny_async_computation_push
 */

bool			bunny_async_computation_foreach(t_bunny_function	fn,
							void			**da,
							size_t			len)
{
  bool			once = true;
  size_t		i;

  for (i = 0; i < len; ++i)
    if (bunny_async_computation_push(fn, da[i]) == false)
      once = false;
    else
      da[i] = NULL;
  return (once);
}

