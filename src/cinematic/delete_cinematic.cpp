// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

void			bunny_delete_cinematic(t_bunny_cinematic	*_cin)
{
  struct bunny_cinematic *cin = (struct bunny_cinematic*)_cin;
  t_bunny_map		**nod;

  for (bunny_map_all(cin->pictures, nod))
    bunny_delete_clipable(bunny_map_data(*nod, t_bunny_clipable*));
  bunny_delete_map(cin->pictures);

  for (bunny_map_all(cin->fonts, nod))
    bunny_delete_clipable(bunny_map_data(*nod, t_bunny_clipable*));
  bunny_delete_map(cin->fonts);

  for (bunny_map_all(cin->effects, nod))
    bunny_delete_sound(bunny_map_data(*nod, t_bunny_sound*));
  bunny_delete_map(cin->effects);

  for (bunny_map_all(cin->musics, nod))
    bunny_delete_sound(bunny_map_data(*nod, t_bunny_sound*));
  bunny_delete_map(cin->musics);

  for (bunny_map_all(cin->voices, nod))
    bunny_delete_sound(bunny_map_data(*nod, t_bunny_sound*));
  bunny_delete_map(cin->voices);

  bunny_delete_map(cin->texts);
  bunny_delete_map(cin->commands);

  delete cin->sprite;
  delete cin->texture;
  delete cin;
}
