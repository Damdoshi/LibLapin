/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
*/

#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_picture		*pic;
t_bunny_picture		*final;
bool			display_final;
t_bunny_normal_map	normal_map =
  {
    .window_size = {0, 0},
    .normal_map = NULL,
    .specular_map = NULL,
    .lights = {
      [0] = {
	.active = true,
	.x = 20,
	.y = 20,
	.z = 1.0,
	.light_color = { .full = WHITE },
	.light_attenuation = 0.5,

	.ambient_color = { .full = WHITE },
	.ambient_depth = 0.3,
	.ambient_attenuation = 4.0,

	.specular_color = { .full = WHITE },
	.specular_depth = 0.3,
	.specular_attenuation = 1.0
      },
      [1 ... 7] = { .active = false }
    }
  };

t_bunny_response	key(t_bunny_event_state			state,
			    t_bunny_keysym			sym,
			    void				*data)
{
  (void)state;
  (void)data;
  if (state == GO_UP)
    return (GO_ON);
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (sym == BKS_SPACE)
    bunny_swap_color_and_normal_map(pic);
  if (sym == BKS_RETURN)
    display_final = !display_final;
  return (GO_ON);
}

t_bunny_response	mouse_move(const t_bunny_position	*rel,
				   void				*data)
{
  (void)rel;
  (void)data;
  return (GO_ON);
}

t_bunny_response	loop(void				*dat)
{
  (void)dat;
  normal_map.lights[0].x = bunny_get_mouse_position()->x;
  normal_map.lights[0].y = bunny_get_mouse_position()->y;
  if (display_final)
    bunny_blit_shader(&win->buffer, pic, NULL, bunny_normal_map_shader(&normal_map));
  else
    bunny_blit(&win->buffer, pic, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  display_final = false;
  bunny_normal_map_shader(&normal_map);
  assert((pic = bunny_load_picture("./pic.psd")));
  bunny_blit(&pic->buffer, bunny_load_picture("./pic2.psd"), NULL);
  assert((win = bunny_start(pic->buffer.width, pic->buffer.height, false, "NormalPicture")));
  normal_map.window_size.x = win->buffer.width;
  normal_map.window_size.y = win->buffer.height;
  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_set_move_response(mouse_move);
  bunny_loop(win, 50, NULL);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
