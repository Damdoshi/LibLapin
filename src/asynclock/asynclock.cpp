// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static int		remove_dead_trap(struct bunny_trap	**trap,
					 t_bunny_call_order	order)
{
  struct bunny_trap	*lst;
  struct bunny_trap	*nxt;
  int			cnt;

  cnt = 0;
  for (lst = *trap; lst != NULL; )
    if (lst->remove_it)
      {
	nxt = lst->next;
	__bunny_delete_trap(lst, order);
	lst = nxt;
      }
    else
      {
	cnt += 1;
	lst = lst->next;
      }
  return (cnt);
}

static void		asyncall(double				elapsed,
				 struct bunny_trap		*lst,
				 double				now)
{
  // Call the function between time A and B
  if (lst->duration > 0.001)
    {
      if (lst->start_time < now && lst->start_time + lst->duration > now)
	lst->func(elapsed, (t_bunny_trap*)lst, lst->param);
      else if (lst->start_time + lst->duration < now)
	lst->remove_it = true;
    }
  // Call the function every duration -seconds
  else if (lst->duration < -0.001)
    {
      if (lst->start_time < now && lst->start_time - lst->duration > now)
	{
	  lst->func(elapsed, (t_bunny_trap*)lst, lst->param);
	  lst->start_time -= lst->duration;
	}
      else if (lst->start_time - lst->duration < now)
	lst->start_time -= lst->duration;
    }
  // Call the function one single time at start_time
  else
    {
      if (lst->start_time > now - elapsed &&
	  lst->start_time <= now)
	{
	  lst->func(elapsed, (t_bunny_trap*)lst, lst->param);
	  lst->remove_it = true;
	}
    }
}

static int		asynclock(double			elapsed,
				  struct bunny_trap		**trap,
				  t_bunny_call_order		order)
{
  struct bunny_trap	*lst;
  double		now;

  now = bunny_get_current_time();
  for (lst = *trap; lst != NULL; lst = lst->next)
    if (lst->start_time > 0)
      asyncall(elapsed, lst, now);
    else if (lst == *trap)
      asyncall(elapsed, lst, now);
  return (remove_dead_trap(trap, order));
}

/**
 * @doc
 * @doc-symbol bunny_asynclock
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Evaluates registered traps for one call order.
 * @description bunny_asynclock browses the traps registered for the selected call order, calls the matching functions when their timing conditions are fulfilled, and deletes traps that were marked for removal.
 * @description You usually should not call this function directly when using bunny_loop or bunny_loop_mw, because these loop functions already call it.
 * @param elapsed_time The elapsed time since the previous asynclock step, in seconds. It is transmitted to trap callbacks.
 * @param order Selects whether traps registered before or after the main loop function are evaluated.
 * @return-case success On $Bsuccess@, returns the number of traps still registered for the selected call order.
 * @see bunny_new_trap, bunny_delete_trap, bunny_loop
 *
 * @doc-lang fr
 * @brief Évalue les traps enregistrées pour un ordre d'appel.
 * @description bunny_asynclock parcourt les traps enregistrées pour l'ordre d'appel sélectionné, appelle les fonctions correspondantes lorsque leurs conditions de temps sont remplies et détruit les traps marquées pour suppression.
 * @description Vous ne devriez généralement pas appeler cette fonction directement lorsque vous utilisez bunny_loop ou bunny_loop_mw, car ces fonctions de boucle l'appellent déjà.
 * @param elapsed_time Le temps écoulé depuis l'étape asynclock précédente, en secondes. Il est transmis aux callbacks des traps.
 * @param order Sélectionne si les traps enregistrées avant ou après la fonction principale de boucle sont évaluées.
 * @return-case success En cas de $Bsuccès@, renvoie le nombre de traps encore enregistrées pour l'ordre d'appel sélectionné.
 * @see bunny_new_trap, bunny_delete_trap, bunny_loop
 */
int			bunny_asynclock(double			elapsed_time,
					t_bunny_call_order	order)
{
  if (order == BCO_BEFORE_LOOP_MAIN_FUNCTION)
    return (asynclock(elapsed_time, &gl_bunny_trap_head[0], order));
  return (asynclock(elapsed_time, &gl_bunny_trap_head[2], order));
}
