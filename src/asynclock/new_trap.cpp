// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN					\
  "%p func, %d order, %f start, %f duration, %p duration -> %p"

struct bunny_trap		*gl_bunny_trap_head[4];

/**
 * @doc
 * @doc-symbol bunny_new_trap
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Creates a new asynclock trap.
 * @description bunny_new_trap creates and registers a trap, that is, a callback called by bunny_asynclock when its timing condition is fulfilled. The trap can later be removed with bunny_delete_trap.
 * @section Timing rules If start_time is positive and duration is positive, function is called while the current bunny-clock time is between start_time and start_time + duration. If duration is near zero, function is called once after start_time. If duration is negative, function is called repeatedly every -duration seconds once start_time has been reached.
 * @section Queued traps If start_time is negative or zero, the trap waits until previously registered traps in the same call order have completed their work, then follows the same duration rules.
 * @param function The function to call when the configured condition is fulfilled.
 * @param order Selects whether the trap is evaluated before or after the main loop function.
 * @param start_time The start time, in seconds, or a non-positive value for a queued trap.
 * @param duration The active duration or repeat period, in seconds.
 * @param param The arbitrary pointer sent as the third parameter of function.
 * @return-case success On $Bsuccess@, returns a valid t_bunny_trap pointer.
 * @return-case failure On $Bfailure@, returns $CNULL@.
 * @error ENOMEM Out of memory.
 * @log "asynclock"
 * @see bunny_delete_trap, bunny_asynclock, bunny_loop
 *
 * @doc-lang fr
 * @brief Crée une nouvelle trap asynclock.
 * @description bunny_new_trap crée et enregistre une trap, c'est-à-dire un callback appelé par bunny_asynclock lorsque sa condition de temps est remplie. La trap peut ensuite être retirée avec bunny_delete_trap.
 * @section Règles de temps Si start_time est positif et duration est positive, function est appelée tant que le temps courant de l'horloge bunny est compris entre start_time et start_time + duration. Si duration est proche de zéro, function est appelée une seule fois après start_time. Si duration est négative, function est appelée de manière répétée toutes les -duration secondes une fois start_time atteint.
 * @section Traps en file Si start_time est négatif ou nul, la trap attend que les traps enregistrées avant elle dans le même ordre d'appel aient terminé leur travail, puis suit les mêmes règles de duration.
 * @param function La fonction à appeler lorsque la condition configurée est remplie.
 * @param order Sélectionne si la trap est évaluée avant ou après la fonction principale de boucle.
 * @param start_time Le temps de départ, en secondes, ou une valeur non positive pour une trap en file.
 * @param duration La durée active ou période de répétition, en secondes.
 * @param param Le pointeur arbitraire envoyé comme troisième paramètre de function.
 * @return-case success En cas de $Bsuccès@, renvoie un pointeur t_bunny_trap valide.
 * @return-case failure En cas d'$Béchec@, renvoie $CNULL@.
 * @error ENOMEM Mémoire insuffisante.
 * @log "asynclock"
 * @see bunny_delete_trap, bunny_asynclock, bunny_loop
 */
t_bunny_trap			*bunny_new_trap(t_bunny_trap_function	function,
						t_bunny_call_order	order,
						double			start_time,
						double			duration,
						void			*param)
{
  struct bunny_trap		**snt;
  struct bunny_trap		*trap;

  if (order == BCO_BEFORE_LOOP_MAIN_FUNCTION)
    snt = &gl_bunny_trap_head[0];
  else
    snt = &gl_bunny_trap_head[2];

  if ((trap = (struct bunny_trap*)bunny_malloc(sizeof(*trap))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "asynclock",
		    function, order, start_time, duration, param, trap);
  trap->next = NULL;
  trap->prev = NULL;
  trap->remove_it = false;
  trap->start_time = start_time;
  trap->duration = duration;
  trap->func = function;
  trap->param = param;
  if (snt[0] == NULL)
    {
      snt[0] = trap;
      snt[1] = trap;
    }
  else
    {
      snt[1]->next = trap;
      trap->prev = snt[1];
      snt[1] = trap;
    }
  scream_log_if(PATTERN, "asynclock", function, order, start_time, duration, param, trap);
  return ((t_bunny_trap*)trap);
}
