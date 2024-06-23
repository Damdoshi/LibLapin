/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<time.h>
#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_picture		*layout;
t_bunny_picture		*screen;
t_bunny_picture		*buffers;
t_bunny_shader		*shader;
bool			display;

t_bunny_response	key(t_bunny_event_state			state,
			    t_bunny_keysym			sym,
			    void				*data)
{
  (void)state;
  (void)data;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	move(const t_bunny_position		*relative,
			     void				*dat)
{
  (void)relative;
  (void)dat;
  return (GO_ON);
}

t_bunny_response	loop(void				*dat)
{
  int			i;

  (void)dat;
  bunny_clear(&win->buffer, BLACK);
  bunny_shader_set_variable(shader, "Random", BVT_1_FLOAT, rand() / 256.0);
  buffers->color_mask.argb[ALPHA_CMP] = 255;

  for (i = 0; i < 10; ++i)
    bunny_blit_shader(&buffers->buffer, buffers, NULL, shader);

  buffers->color_mask.argb[ALPHA_CMP] = 32;
  bunny_blit(&screen->buffer, buffers, NULL);
  bunny_blit(&win->buffer, screen, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{ 
  t_bunny_position	pos;

  srand(time(NULL));
  assert(bunny_is_shader_available());
  assert(shader = bunny_new_shader());
  assert(bunny_load_shader(shader, "spread.vert", "spread.frag"));

  assert(layout = bunny_load_picture("layout.png"));
  assert(win = bunny_start(layout->buffer.width, layout->buffer.height, false, "Spreading"));
  assert(screen = bunny_new_picture(layout->buffer.width, layout->buffer.height));
  assert(buffers = bunny_new_picture(layout->buffer.width, layout->buffer.height));

  bunny_clear(&buffers->buffer, BLACK);
  bunny_clear(&screen->buffer, BLACK);
  bunny_clear(&win->buffer, BLACK);

  pos.x = layout->buffer.width / 2.0;
  pos.y = layout->buffer.height / 2.0;
  bunny_set_pixel(&buffers->buffer, pos, WHITE);
  
  bunny_shader_set_variable(shader, "Previous", BVT_CURRENT_TEXTURE_TYPE);
  bunny_shader_set_variable(shader, "Layout", BVT_PICTURE, layout);

  bunny_set_key_response(key);
  bunny_set_move_response(move);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 20, NULL);

  bunny_delete_clipable(buffers);
  bunny_delete_clipable(layout);
  bunny_delete_clipable(screen);
  bunny_delete_shader(shader);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
