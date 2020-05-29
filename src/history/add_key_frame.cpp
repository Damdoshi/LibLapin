// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

bool			bunny_historic_element_add_key_frame(t_bunny_historic_element	*elem,
							     int64_t			tick,
							     void			*data)
{
  if (tick < 0)
    return (false);
  char			*array = (char*)&elem->status[0];
  size_t		stlen = sizeof(*elem->status) + elem->status_length + elem->status_length % 8;
  int64_t		ctick = tick % elem->status_array_length;
  t_bunny_historic_state *state = (t_bunny_historic_state*)&array[ctick * stlen];

    // Le status est maintenant une frame clef.
  state->key_frame = true;
  // On note son tickstamp
  state->tick = tick;
  // On copie la donnée passée en paramètre
  memcpy(&state->data[0], data, elem->status_length);

  // Si le dernier tick calculé est derrière le nouveau
  if (elem->last_tick < tick)
    elem->last_tick = tick;
  // Si le dernier tick imposé est avant celui envoyé, alors on le déplace
  if (elem->last_key_frame_tick < tick)
    elem->last_key_frame_tick = tick;
  return (true);
}

