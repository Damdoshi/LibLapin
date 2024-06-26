/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

void			every_second(double			elapsed,
				     struct s_bunny_trap	*trp,
				     void			*data)
{
  t_bunny_window	*win = data;

  (void)elapsed;
  (void)trp;
  bunny_clear(&win->buffer, rand() | BLACK);
  bunny_display(win);
}

void			initial_blink(double			elapsed,
				      struct s_bunny_trap	*trp,
				      void			*data)
{
  t_bunny_window	*win = data;
  t_bunny_color		col;

  printf("Initial_blink!\n");

  (void)elapsed;
  (void)trp;
  col.full = BLACK;
  col.argb[RED_CMP] = rand() % 255;
  bunny_clear(&win->buffer, col.full);
  bunny_display(win);
}

t_bunny_response	key(t_bunny_event_state			state,
			    t_bunny_keysym			sym,
			    void				*data)
{
  (void)data;
  if (state == GO_DOWN && sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int			main(void)
{
  t_bunny_window	*win = bunny_start
    (800, 600, false, "Wait & Change");

  assert(win != NULL);

  t_bunny_trap		*trap = bunny_new_trap
    (initial_blink,
     BCO_BEFORE_LOOP_MAIN_FUNCTION,
     3,
     0,
     win
     );
  assert(trap != NULL);

  trap = bunny_new_trap
    (initial_blink,
     BCO_BEFORE_LOOP_MAIN_FUNCTION,
     4,
     0,
     win
     );
  assert(trap != NULL);

  trap = bunny_new_trap
    (initial_blink,
     BCO_BEFORE_LOOP_MAIN_FUNCTION,
     5,
     0,
     win
     );
  assert(trap != NULL);

  trap = bunny_new_trap
    (every_second,
     BCO_BEFORE_LOOP_MAIN_FUNCTION,
     0,
     -1,
     win
     );
  assert(trap != NULL);

  bunny_clear((t_bunny_buffer*)win, BLACK);
  bunny_display(win);
  bunny_set_key_response(key);
  bunny_loop(win, 25, win);
  bunny_delete_trap(trap);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
