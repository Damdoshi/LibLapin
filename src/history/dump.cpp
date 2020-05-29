// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

void			bunny_historic_element_dump(t_bunny_historic_element	*e,
						    t_bunny_historic_dump	d)
{
  size_t		stlen = sizeof(*e->status) + e->status_length + e->status_length % 8;
  char			*arr = (char*)&e->status[0];

  for (size_t i = 0; i < e->status_array_length; ++i)
    {
      t_bunny_historic_state *st = (t_bunny_historic_state*)&arr[i * stlen];

      d(st->tick, &st->data[0]);
    }
}

