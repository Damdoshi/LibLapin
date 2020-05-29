// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

void			*bunny_historic_element_last_status(t_bunny_historic_element	*elem)
{
  if (elem->last_tick == -1)
    return (NULL);
  size_t		stlen = sizeof(*elem->status) + elem->status_length + elem->status_length % 8;
  int64_t		last_status = elem->last_tick % elem->status_array_length;
  char			*arr = (char*)&elem->status[0];
  t_bunny_historic_state *tar = (t_bunny_historic_state*)&arr[last_status * stlen];

  return (&tar->data[0]);
}

