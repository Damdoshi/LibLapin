
#include		<iostream>
#include		<time.h>
#include		<math.h>
#include		<alloca.h>
#include		<time.h>
#include		<stdlib.h>
#include		"lapin.h"

t_bunny_window		*win;
t_bunny_picture		*pic;
t_bunny_vertex_array	*array;
double			i;
double			j;

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*data)
{
  (void)state; (void)data;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	click(t_bunny_event_state	state,
			      t_bunny_mouse_button	button,
			      void			*data)
{
  const t_bunny_position *pos = bunny_get_mouse_position();
  t_bunny_accurate_position x;

  (void)button;
  (void)data;
  x.x = pos->x;
  x.y = pos->y;
  if (state == GO_UP)
    return (GO_ON);
  if (bunny_quad_collision_dot(array, &x))
    std::cout << "Clicked on" << std::endl;
  return (GO_ON);
}

t_bunny_response	loop(void			*data)
{
  (void)data;
  for (i = 0; i < 4; ++i)
    {
      array->vertex[(int)i].color = rand() | BLACK;
      array->vertex[(int)i].pos.x = (win->buffer.width + cos(2 * j) * 700 * cos((i + j) * M_PI / 2)) / 2;
      array->vertex[(int)i].pos.y = (win->buffer.height + sin(1.5 * j) * 700 * sin((i + j) * M_PI / 2)) / 2;
    }

  j += 0.03;
  bunny_fill(&win->buffer, ALPHA(16, BLACK));
  bunny_set_geometry(&win->buffer, BGY_QUADS, array, pic);
  bunny_display(win);
  return (GO_ON);
}

int			main(int	argc,
			     char	**argv)
{
  j = 0;
  srand(time(NULL));

  std::cout << "Click on the bunny" << std::endl;

  win = bunny_start(800, 600, false, "");
  if ((pic = bunny_load_picture(argc == 2 ? argv[1] : "bunny.png")) == NULL)
    return (0);

  bunny_clear(&win->buffer, BLACK);

  array = (t_bunny_vertex_array*)bunny_alloca(sizeof(*array) + 4 * sizeof(t_bunny_vertex));
  array->length = 4;

  array->vertex[0].tex.x = 0;
  array->vertex[0].tex.y = 0;

  array->vertex[1].tex.x = pic->buffer.width;
  array->vertex[1].tex.y = 0;

  array->vertex[2].tex.x = pic->buffer.width;
  array->vertex[2].tex.y = pic->buffer.height;

  array->vertex[3].tex.x = 0;
  array->vertex[3].tex.y = pic->buffer.height;

  bunny_set_click_response(click);
  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 20, NULL);
  bunny_delete_clipable(pic);
  bunny_freea(array);
  bunny_stop(win);
  return (0);
}

