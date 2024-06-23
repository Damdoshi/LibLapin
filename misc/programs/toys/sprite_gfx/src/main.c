/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<time.h>
#include		<stdlib.h>
#include		<signal.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_sprite		*backforth;
t_bunny_sprite		*double_forward;

t_bunny_response	display(void		*d)
{
  t_bunny_position	pos;

  (void)d;
  pos.x = 0;
  pos.y = 0;
  bunny_clear(&win->buffer, rand() | BLACK);
  bunny_sprite_animate(backforth, 1.0 / bunny_get_frequency());
  bunny_sprite_animate(double_forward, 1.0 / bunny_get_frequency());
  bunny_blit(&win->buffer, &backforth->clipable, &pos);
  pos.x = 0;
  pos.y = backforth->clipable.clip_height;
  bunny_blit(&win->buffer, &double_forward->clipable, &pos);

  bunny_display(win);

  if (bunny_sprite_is_still(backforth) &&
      bunny_sprite_is_still(double_forward))
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int			main(void)
{
  bunny_set_log_mode(true);
  bunny_set_error_descriptor(2);
  bunny_enable_full_blit(true);
  assert(backforth = bunny_load_sprite("backforth.dab"));
  assert(double_forward = bunny_load_sprite("double_forward.dab"));
  assert(win = bunny_start(100, 220, false, "The Sprite Test"));
  bunny_set_display_function(display);
  bunny_loop(win, 25, NULL);
  bunny_delete_clipable(backforth);
  bunny_delete_clipable(double_forward);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

