// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

bool			bunny_historic_element_rewind(t_bunny_historic_element	*e,
						      uint64_t			t)
{
  if (t > e->last_tick)
    return (false);
  if (e->last_tick - e->status_array_length > t)
    return (false);
  if ((e->last_status -= e->last_tick - t) < 0)
    e->last_status += e->status_array_length;
  e->last_computed_tick = t;
  return (true);
}

