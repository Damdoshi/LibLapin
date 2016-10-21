// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

struct bunny_trap		*gl_bunny_trap_head[4];

t_bunny_trap			*bunny_new_trap(t_bunny_trap_function	func,
						t_bunny_call_order	order,
						double			start,
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
    return (NULL);
  trap->next = NULL;
  trap->remove_it = false;
  trap->start_time = start;
  trap->duration = duration;
  trap->func = func;
  trap->param = param;
  if (snt[0] == NULL)
    {
      snt[0] = trap;
      snt[1] = trap;
    }
  else
    {
      snt[1]->next = trap;
      if (snt[0] != snt[1])
	trap->prev = snt[1];
      else
	trap->next = NULL;
    }
  return ((t_bunny_trap*)trap);
}

