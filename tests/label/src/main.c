/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#include		<lapin.h>
#include		<assert.h>

t_bunny_response	general_display(void		*d)
{
  t_bunny_box_system	*bs = d;
  t_bunny_window	*win = (t_bunny_window*)bs->head.screen;

  bunny_display(win);
  bunny_clear(&win->buffer, PINK2);
  return (GO_ON);
}

int			main(void)
{
  static t_bunny_box_system bs;
  t_bunny_configuration	*cnf;
  t_bunny_configuration	*screen;

  bunny_set_log_mode(true);
  bunny_set_error_descriptor(2);

  /*
  assert(screen = bunny_open_configuration("gui.dab", NULL));
  assert(bunny_save_configuration(BC_DABSIC, "/dev/stdout", screen));
  bunny_delete_configuration(screen);
  */

  assert(bs.head.screen = (t_bunny_buffer*)bunny_start(1440, 900, false, "Box System"));
  bs.head.main_structure = bs.head.screen;

  assert(cnf = bunny_init_box_environ(bs.head.screen->width, bs.head.screen->height));
  assert(bunny_load_box(&bs, "./gui.dab", cnf));
  assert(bs.screen.type == BBT_SIMPLE_BOX);
  assert(bs.screen.parent == NULL);
  assert(bunny_configuration_getf(cnf, &screen, "Screen"));
  assert(bs.screen.configuration == screen);
  assert(bs.screen.position.x == 0);
  assert(bs.screen.position.y == 0);
  assert(bs.screen.size.x == bs.head.screen->width);
  assert(bs.screen.size.y == bs.head.screen->height);

  bunny_set_context(&gl_bunny_box_context);
  bs.head.subcontext.display = general_display;
  bunny_loop((t_bunny_window*)bs.head.screen, 25, &bs);
  bunny_stop((t_bunny_window*)bs.head.screen);
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", cnf);
  return (EXIT_SUCCESS);
}

