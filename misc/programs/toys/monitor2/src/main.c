/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Mathematic evaluation function test program
*/

#include		<assert.h>
#include		<stdio.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_font		*font;
int			val0 = 0;
int			val1 = 0;
double			val2 = 0;

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*data)
{
  (void)sym;
  (void)data;
  if (state == GO_DOWN)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	loop(void			*data)
{
  (void)data;

  val0 += 1;
  val1 += 2;
  val2 += 4;

  bunny_clear(&win->buffer, BLACK);
  bunny_clear(&font->clipable.buffer, BLACK);
  bunny_display_monitored_value(font, NULL);
  bunny_blit(&win->buffer, &font->clipable, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  static const t_bunny_position siz = {10 * 3, 14 * 3};

  assert(win = bunny_start(800, 600, false, "Monitor"));
  assert(font = bunny_load_font
	 (win->buffer.width, win->buffer.height, "./font.ttf", &siz));
  font->clipable.position.x = 50;
  font->clipable.position.y = 50;

  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);

  bunny_add_monitored_value("val0", &val0);
  bunny_add_monitored_value("val1", &val1);
  bunny_add_monitored_value("val2", &val2);

  bunny_loop(win, 25, NULL);

  bunny_delete_clipable(&font->clipable);
  bunny_stop(win);
  return (0);
}

