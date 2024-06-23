/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** Joystick vibration
*/

#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_picture		*pic;

t_bunny_response	axis(int		id,
			     t_bunny_axis	ax,
			     float		v,
			     void		*d)
{
  (void)id;
  (void)ax;
  (void)v;
  (void)d;
  return (GO_ON);
}

t_bunny_response	button(t_bunny_event_state st,
			       int		id,
			       int		but,
			       void		*dat)
{
  (void)dat;
  (void)but;
  if (st == GO_DOWN && id == 0)
    {
    }
  return (GO_ON);
}

t_bunny_response	loop(void		*e)
{
  (void)e;
  float		a = bunny_get_joy_axis()[0][2];

  if ((a = ((a + 100) / 200.0)) < 0.1)
    a = 0;
  else if (a > 0.9)
    a = 1.0;
  bunny_set_joystick_vibration(0, a);
  return (GO_ON);
}

t_bunny_response	key(t_bunny_event_state	s,
			    t_bunny_keysym	k,
			    void		*d)
{
  (void)d;
  (void)s;
  if (k == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	display(void		*e)
{
  float			a = bunny_get_joy_axis()[0][2]; // left vibe

  (void)e;

  a = (a + 100) / 200.0;
  
  pic->clip_x_position = 0;
  pic->clip_y_position = 0;
  pic->clip_width = pic->buffer.width;
  pic->clip_height = pic->buffer.height;
  
  bunny_fill(&pic->buffer, BLACK);

  pic->clip_width = pic->buffer.width;
  pic->clip_height = a * pic->buffer.height;
  bunny_fill(&pic->buffer, RED);
  
  bunny_blit(&win->buffer, pic, NULL);
  bunny_display(win);
  
  return (GO_ON);
}

t_bunny_response	joyconnect(t_bunny_event_state	state,
				   int			id,
				   const t_bunny_joystick	*info,
				   void			*d)
{
  (void)state;
  (void)id;
  (void)info;
  (void)d;
  return (GO_ON);
}

int			main(void)
{
  assert((win = bunny_start(800, 600, false, "Vibration test")));
  bunny_clear(&win->buffer, BLACK);
  assert((pic = bunny_new_picture(win->buffer.width, win->buffer.height)));
  bunny_clear(&pic->buffer, BLACK);

  bunny_set_error_descriptor(2);
  bunny_set_joy_connect_response(joyconnect);
  bunny_set_joy_axis_response(axis);
  bunny_set_joy_button_response(button);
  bunny_set_loop_main_function(loop);
  bunny_set_display_function(display);
  bunny_set_key_response(key);
  bunny_loop(win, 50, NULL);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
