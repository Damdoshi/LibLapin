// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

bool			bunny_historic_element_rewind(t_bunny_historic_element	*e,
						      int64_t			t)
{
  // Si on veut remonter dans le futur, on ne le fait pas
  if (t > e->last_tick)
    return (false);
  // Si on veut remonter avant une frame clef, on ne le fait pas
  if (t < e->last_key_frame_tick)
    t = e->last_key_frame_tick;
  // Si on veut remontrer trop loin dans le passé, on ne le fait pas
  if (e->last_tick - (int64_t)e->status_array_length > t)
    return (false);
  e->last_tick = t;
  return (true);
}

