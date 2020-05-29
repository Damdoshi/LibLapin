// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include	"lapin_private.h"

int64_t	bunny_history_count_events_since(t_bunny_event_history *_his,
					 int64_t		tick)
{
  struct bunny_event_history *his = (struct bunny_event_history*)_his;
  auto it = his->events.lower_bound(tick);
  int64_t	z = 0;

  for (; it != his->events.end(); ++it)
    z += it->second.size();
  return (z);
}

int64_t	bunny_history_count_events_of(t_bunny_event_history *_his,
				      int64_t		tick)
{
  struct bunny_event_history *his = (struct bunny_event_history*)_his;
  auto it = his->events.lower_bound(tick);
  int64_t	z = 0;

  if (it->first != tick)
    return (0);
  z += it->second.size();
  return (z);
}

