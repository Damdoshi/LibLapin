// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

void			bunny_cinematic_stop(t_bunny_cinematic	*_cin)
{
  struct bunny_cinematic *cin = (struct bunny_cinematic*)_cin;
  t_bunny_map		**nod;

  for (bunny_map_all(cin->effects, nod))
    bunny_sound_stop(bunny_map_data(*nod, t_bunny_sound*));
  for (bunny_map_all(cin->musics, nod))
    bunny_sound_stop(bunny_map_data(*nod, t_bunny_sound*));
  for (bunny_map_all(cin->voices, nod))
    bunny_sound_stop(bunny_map_data(*nod, t_bunny_sound*));
}
