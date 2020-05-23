// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include	"lapin_private.h"

void		bunny_delete_event_history(t_bunny_event_history	*_his)
{
  struct bunny_event_history *his = (struct bunny_event_history*)_his;

  for (auto it = his->events.begin(); it != his->events.end(); ++it)
    for (auto itx = it->second.begin(); itx != it->second.end(); ++itx)
      bunny_free(*itx);
  delete his;
}

