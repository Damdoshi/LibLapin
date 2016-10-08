/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<stdio.h>
#include		<lapin.h>

t_bunny_window		*win;
bool			visible;
int			inc;

t_bunny_response	key(t_bunny_event_state s, t_bunny_keysym k, void *data)
{
  (void)data;
  if (s == GO_DOWN && k == BKS_SPACE)
    {
      visible = !visible;
      bunny_set_mouse_visibility(win, visible);
    }
  return (GO_ON);
}

t_bunny_response	loop(void		*data)
{
  (void)data;
  bunny_clear(&win->buffer, (inc += 10) | BLACK);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  inc = 0;
  visible = true;
  puts("Appuyez sur espace pour faire apparaitre ou disparaitre la souris.");
  win = bunny_start(800, 600, false, "");
  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 25, NULL);
  bunny_stop(win);
  return (0);
}
