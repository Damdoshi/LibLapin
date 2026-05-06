// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			__bunny_delete_trap(struct bunny_trap		*trap,
				    t_bunny_call_order		order)
{
  struct bunny_trap	**snt;

  scream_log_if("%p trap, %d order", "asynclock", trap, order);

  if (order == BCO_BEFORE_LOOP_MAIN_FUNCTION)
    snt = &gl_bunny_trap_head[0];
  else
    snt = &gl_bunny_trap_head[2];

  if (snt[0] == trap)
    snt[0] = trap->next;
  if (snt[1] == trap)
    snt[1] = trap->prev;

  if (trap->prev)
    trap->prev->next = trap->next;
  if (trap->next)
    trap->next->prev = trap->prev;

  bunny_free(trap);
}

/**
 * @doc
 * @doc-symbol bunny_delete_trap
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Removes a trap from the asynclock system.
 * @description bunny_delete_trap marks the sent trap for deletion. The trap is effectively destroyed by bunny_asynclock when it can safely browse its trap list, so this function can be called from inside a t_bunny_trap_function callback.
 * @param trap The trap to remove. It must be a valid trap created by bunny_new_trap.
 * @log "asynclock"
 * @see bunny_new_trap, bunny_asynclock, bunny_loop
 *
 * @doc-lang fr
 * @brief Retire une trap du système asynclock.
 * @description bunny_delete_trap marque la trap envoyée pour suppression. La trap est réellement détruite par bunny_asynclock lorsqu'elle peut parcourir sa liste de traps sans risque, cette fonction peut donc être appelée depuis un callback t_bunny_trap_function.
 * @param trap La trap à retirer. Elle doit être une trap valide créée par bunny_new_trap.
 * @log "asynclock"
 * @see bunny_new_trap, bunny_asynclock, bunny_loop
 */
void			bunny_delete_trap(t_bunny_trap			*_trap)
{
  struct bunny_trap	*trap = (struct bunny_trap*)_trap;

  scream_log_if("%p", "asynclock", trap);
  trap->remove_it = true;
}
