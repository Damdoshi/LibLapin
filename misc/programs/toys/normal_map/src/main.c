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
t_bunny_picture		*picture;
double			rot;
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
  return (GO_ON);
}

t_bunny_response	mouse_move(const t_bunny_position	*rel,
				   void				*data)
{
  //const t_bunny_position *pos = bunny_get_mouse_position();

  (void)rel;
  (void)data;
  /*
    normal_map.lights[0].x = pos->x;
    normal_map.lights[0].y = pos->y;
  */
  return (GO_ON);
}

t_bunny_response	loop(void				*dat)
{
  static t_bunny_position siz = {10, 10};
  t_bunny_position	pos;

  (void)dat;
  bunny_clear(&win->buffer, BLACK);
  normal_map.lights[0].x = pos.x = (1 + 0.8 * cos(rot += M_PI / 128)) * win->buffer.width / 2;
  normal_map.lights[0].y = pos.y = (1 + 0.8 * sin(rot += M_PI / 128)) * win->buffer.height / 2;
  bunny_blit_shader(&win->buffer, picture, NULL, bunny_normal_map_shader(&normal_map));
  bunny_set_circle(&win->buffer, pos, siz, ALPHA(128, rand()));
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  assert(picture = bunny_load_picture("color.png"));
  assert(normal_map.normal_map = bunny_load_picture("normal.png"));
  assert(normal_map.specular_map = bunny_load_picture("specular.png"));
  assert(win = bunny_start(picture->clip_width, picture->clip_height, false, "NormalMap"));

  rot = 0;
  normal_map.window_size.x = picture->clip_width;
  normal_map.window_size.y = picture->clip_height;

  bunny_set_key_response(key);
  bunny_set_move_response(mouse_move);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 20, NULL);

  bunny_delete_clipable(picture);
  bunny_delete_clipable(normal_map.normal_map);
  bunny_delete_clipable(normal_map.specular_map);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
