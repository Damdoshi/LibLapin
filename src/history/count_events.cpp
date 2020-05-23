// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include	"lapin_private.h"

uint64_t	bunny_history_count_events(t_bunny_event_history *_his,
					   uint64_t		tick)
{
  struct bunny_event_history *his = (struct bunny_event_history*)_his;
  auto it = his->events.lower_bound(tick);
  uint64_t	z = 0;

  for (; it != his->events.end(); ++it)
    z += it->second.size();
  return (z);
}

