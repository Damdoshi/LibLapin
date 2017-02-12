// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
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
	lst->func(elapsed, (t_bunny_trap*)lst, lst->param);
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

int			bunny_asynclock(double			elapsed,
					t_bunny_call_order	order)
{
  elapsed /= 1e6; // us to seconds
  if (order == BCO_BEFORE_LOOP_MAIN_FUNCTION)
    return (asynclock(elapsed, &gl_bunny_trap_head[0], order));
  return (asynclock(elapsed, &gl_bunny_trap_head[2], order));
}

