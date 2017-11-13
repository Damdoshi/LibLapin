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
    (800, 600, false, "Wait & Blink 1 second");

  assert(win != NULL);

  t_bunny_trap		*trap = bunny_new_trap
    (every_second,
     BCO_BEFORE_LOOP_MAIN_FUNCTION,
     5,
     1,
     win
     );

  assert(trap != NULL);

  printf("Must wait 5 seconds, and then change color every second.");

  bunny_clear((t_bunny_buffer*)win, BLACK);
  bunny_display(win);
  bunny_set_key_response(key);
  bunny_loop(win, 25, win);
  bunny_delete_trap(trap);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
