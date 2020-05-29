// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

void			bunny_history_clear_before(t_bunny_event_history	*his,
						   uint64_t			tick)
{
  struct bunny_event_history *h = (struct bunny_event_history*)his;
  auto it = h->events.lower_bound(tick);

  if (it == h->events.begin())
    return ;
  --it;
  h->events.erase(h->events.begin(), it);
}

