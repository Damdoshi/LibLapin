/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<stdio.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_picture	*pic = NULL;
  t_bunny_configuration	*cnf = NULL;

  assert(bunny_set_clipable_attribute("./picture.ini", &pic, &cnf, false));
  bunny_save_configuration(BC_INI, "/dev/stdout", cnf);

  assert(pic->scale.x == 3 && pic->scale.y == 3);
  assert(pic->origin.x == 2 && pic->origin.y == 3);
  assert(pic->rotation == 4);
  assert(pic->position.x == 5 && pic->position.y == 6);
  assert(pic->color_mask.argb[ALPHA_CMP] == 10);
  assert(pic->color_mask.argb[RED_CMP] == 7);
  assert(pic->color_mask.argb[GREEN_CMP] == 8);
  assert(pic->color_mask.argb[BLUE_CMP] == 9);

  assert(pic->clip_x_position == 10);
  assert(pic->clip_y_position == 0);
  assert(pic->clip_width == 10);
  assert(pic->clip_height == 20);

  bunny_delete_clipable(pic);
  bunny_delete_configuration(cnf);
  return (EXIT_SUCCESS);
}

