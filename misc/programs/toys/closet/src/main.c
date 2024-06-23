/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#include		<lapin.h>
#include		<assert.h>
#include		<string.h>

int			main(void)
{
  static t_bunny_position pos = {200, 0};
  t_bunny_window	*win;
  t_bunny_clothe	*clothe;
  t_bunny_map		*map;
  t_bunny_closet	*closet;

  bunny_set_error_descriptor(2);
  bunny_set_log_filter("syntax");

  assert(map = bunny_new_wardrobe());
  assert(closet = bunny_load_closet("./closet.dab", map));

  assert(bunny_map_get_data(map, "Panties", t_bunny_closet*) == closet);
  assert(strcmp(closet->name, "Panties") == 0);
  assert(closet->position.x == 42);
  assert(closet->position.y == 84);
  assert(closet->depth == 3);

  assert(win = bunny_start(600, 200, false, "Panties closet"));

  assert(clothe = bunny_vector_data(closet->clothes, 0, t_bunny_clothe*));
  assert(strcmp(clothe->name, "PinkPanties") == 0);
  bunny_blit(&win->buffer, &clothe->sprite->clipable, NULL);

  assert(clothe = bunny_vector_data(closet->clothes, 1, t_bunny_clothe*));
  assert(strcmp(clothe->name, "GreenPanties") == 0);
  bunny_blit(&win->buffer, &clothe->sprite->clipable, &pos);

  assert(clothe = bunny_vector_data(closet->clothes, 2, t_bunny_clothe*));
  assert(strcmp(clothe->name, "BluePanties") == 0);
  pos.x = 400;
  bunny_blit(&win->buffer, &clothe->sprite->clipable, &pos);

  bunny_display(win);
  bunny_usleep(1e6);

  bunny_stop(win);
  return (EXIT_SUCCESS);
}
