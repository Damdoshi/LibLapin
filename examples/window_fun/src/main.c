/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<signal.h>
#include		<stdlib.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_response	loop(void		*data)
{
  t_bunny_window	*win = data;
  t_bunny_position	screen;
  t_bunny_position	tmp;

  screen = bunny_get_screen_size();
  tmp.x = rand() % screen.x * 0.2 + 50;
  tmp.y = rand() % screen.y * 0.2 + 50;
  bunny_resize_window(win, tmp);
  tmp.x = rand() % (screen.x - win->buffer.width);
  tmp.y = rand() % (screen.y - win->buffer.height);
  bunny_move_window(win, tmp);
  bunny_clear(&win->buffer, rand() | BLACK);
  bunny_display(win);
  return (GO_ON);
}

t_bunny_response	click(t_bunny_event_state	state,
			      t_bunny_mouse_button	button,
			      void			*data)
{
  (void)button;
  (void)data;
  if (state == GO_UP)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int			main(void)
{
  t_bunny_window	*win;
  t_bunny_music		*music;

  printl("Click on the window to stop this insanity.");
  assert(win = bunny_start(800, 600, false, "Never gonna give you up!"));
  assert(music = bunny_load_music("music.ogg"));
  signal(SIGINT, SIG_IGN);
  bunny_sound_play(&music->sound);
  bunny_set_click_response(click);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 5, win);
  bunny_sound_stop(&music->sound);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
