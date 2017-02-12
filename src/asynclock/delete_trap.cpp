// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			__bunny_delete_trap(struct bunny_trap		*trap,
					    t_bunny_call_order		order)
{
  struct bunny_trap	**snt;

  if (order == BCO_BEFORE_LOOP_MAIN_FUNCTION)
    snt = &gl_bunny_trap_head[0];
  else
    snt = &gl_bunny_trap_head[2];

  if (snt[0] == trap)
    snt[0] = trap->next;
  if (snt[1] == trap)
    snt[1] = trap->prev;
  bunny_free(trap);
}

void			bunny_delete_trap(t_bunny_trap			*_trap)
{
  struct bunny_trap	*trap = (struct bunny_trap*)_trap;

  trap->remove_it = true;
}

