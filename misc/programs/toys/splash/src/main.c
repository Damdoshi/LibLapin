/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

t_bunny_response	splash_display_resize(t_bunny_splash_screen	*ss)
{
  static const t_bunny_position bp = {0, 0};
  t_bunny_clipable	*screen = (t_bunny_clipable*)ss->head.screen;
  t_bunny_window	*win = (t_bunny_window*)ss->head.main_structure;

  screen->scale.x = (double)win->buffer.width / screen->buffer.width;
  screen->scale.y = (double)win->buffer.height / screen->buffer.height;
  bunny_blit(&win->buffer, screen, &bp);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  static t_bunny_splash_screen ss;

  assert(ss.head.main_structure = bunny_start(1440, 900, false, "Splash Screen"));
  assert(ss.head.screen = (t_bunny_buffer*)bunny_new_picture(1920, 1080));

  ss.head.subcontext.display = (t_bunny_display)splash_display_resize;
  ss.bunny_picture_file = "./bunny.ini";
  ss.rope_picture_file = "./rope.ini";
  ss.title_picture_file = "./title.ini";
  ss.jingle_sound_file = "./jingle.ini";
  ss.boom_sound_file = "./boom.ini";
  ss.outch_sound_file = "./outch.ini";
  ss.falling_sound_file = "./falling.ini";

  bunny_set_context(&gl_bunny_splash_context);
  bunny_loop((t_bunny_window*)ss.head.main_structure, 40, &ss);
  bunny_delete_clipable((t_bunny_clipable*)ss.head.screen);
  bunny_stop((t_bunny_window*)ss.head.main_structure);
  return (EXIT_FAILURE);
}

