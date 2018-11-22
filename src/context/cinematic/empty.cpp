// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_empty_cinematic(t_bunny_cinematic_screen	*scr)
{
  t_bunny_map		**nod;

  scr->background_color.full = 0;
  scr->foreground_color.full = 0;

  if (scr->pictures)
    {
      for (bunny_map_all(scr->pictures, nod))
	bunny_delete_clipable(bunny_map_data(*nod, t_bunny_clipable*));
      bunny_map_clear(scr->pictures);
    }

  if (scr->text_boxes)
    {
      for (bunny_map_all(scr->text_boxes, nod))
	bunny_delete_clipable(bunny_map_data(*nod, t_bunny_clipable*));
      bunny_map_clear(scr->text_boxes);
    }

  if (scr->voices)
    {
      for (bunny_map_all(scr->voices, nod))
	bunny_delete_sound(bunny_map_data(*nod, t_bunny_sound*));
      bunny_map_clear(scr->voices);
    }

  if (scr->effects)
    {
      for (bunny_map_all(scr->effects, nod))
	bunny_delete_sound(bunny_map_data(*nod, t_bunny_sound*));
      bunny_map_clear(scr->effects);
    }

  if (scr->musics)
    {
      for (bunny_map_all(scr->musics, nod))
	bunny_delete_sound(bunny_map_data(*nod, t_bunny_sound*));
      bunny_map_clear(scr->musics);
    }
}

