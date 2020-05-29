// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include	"lapin_private.h"

int64_t	bunny_history_get_events_since(t_bunny_event_history	*_his,
				       int64_t			tick,
				       t_bunny_historical_event	*evt)
{
  struct bunny_event_history *his = (struct bunny_event_history*)_his;
  auto it = his->events.lower_bound(tick);
  int64_t	z = 0;

  for (; it != his->events.end(); ++it)
    for (auto itx = it->second.begin(); itx != it->second.end(); ++itx)
      memcpy(&evt[z++], *itx, sizeof(*evt));
  return (z);
}

int64_t	bunny_history_get_events_of(t_bunny_event_history	*_his,
				    int64_t			tick,
				    t_bunny_historical_event	*evt)
{
  struct bunny_event_history *his = (struct bunny_event_history*)_his;
  auto it = his->events.lower_bound(tick);
  int64_t	z = 0;

  if (it->first != tick)
    return (0);
  for (auto itx = it->second.begin(); itx != it->second.end(); ++itx)
    memcpy(&evt[z++], *itx, sizeof(*evt));
  return (z);
}

