// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

bool			bunny_history_add_event(t_bunny_event_history *_his,
						uint64_t	tick,
						size_t		event_len,
						void		*event)
{
  struct bunny_event_history *his = (struct bunny_event_history*)_his;
  t_bunny_historical_event *evt = (t_bunny_historical_event*)bunny_malloc(sizeof(*evt));

  if (evt == NULL)
    return (false);
  if ((evt->data = bunny_memdup(event, event_len)) == NULL)
    {
      bunny_free(evt);
      return (false);
    }
  evt->tick = tick;
  evt->length = event_len;

  try
    {
      std::list<t_bunny_historical_event*> &lst = his->events[tick];

      lst.push_back(evt);
    }
  catch (...)
    {
      bunny_free(evt->data);
      bunny_free(evt);
      return (false);
    }
  return (true);
}
