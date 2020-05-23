// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

t_bunny_event_history	*bunny_new_event_history(void)
{
  struct bunny_event_history *his;

  if ((his = new (std::nothrow) struct bunny_event_history) == NULL)
    return (NULL);
  return ((t_bunny_event_history*)his);
}

