/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Collide test
*/

#include		<unistd.h>
#include		<lapin.h>
#include		<stdio.h>
#include		<assert.h>

typedef struct		s_shape
{
  t_bunny_collision	col;
  t_bunny_collide_point	touch;
}			t_shape;

t_bunny_window		*window;
t_bunny_threadpool	*threadpool;
t_bunny_pool		*elements;

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*unused)
{
  t_shape		*shape = elements->data[0];

  (void)unused;
  if (state == GO_UP && sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (state == GO_DOWN)
    {
      if (sym == BKS_F1)
	shape->col.equation.origin_at_center = !shape->col.equation.origin_at_center;
      if (sym == BKS_F2)
	shape->col.equation.flipx = !shape->col.equation.flipx;
      if (sym == BKS_F3)
	shape->col.equation.flipy = !shape->col.equation.flipy;
    }
  return (GO_ON);
}

t_bunny_response	loop(void			*unused)
{
  const t_bunny_position *mouse = bunny_get_mouse_position();
  t_shape		*shape = elements->data[0];
  t_bunny_dot_collision	dot;

  (void)unused;

  dot.type = BCT_DOT;
  dot.coord.x = mouse->x;
  dot.coord.y = mouse->y;

  shape->touch = bunny_collision_equation_dot(&shape->col.equation, &dot);
  return (GO_ON);
}

t_bunny_response	display(void			*unused)
{
  const t_bunny_position *mouse = bunny_get_mouse_position();
  t_shape		*shape = elements->data[0];
  t_bunny_line_collision line;
  t_bunny_dot_collision	dot;

  (void)unused;

  dot.type = BCT_DOT;
  line.type = BCT_LINE;

  bunny_clear(&window->buffer, BLACK);
  bunny_draw_collision_shape
    (&window->buffer, &shape->col, shape->touch.radian > 0 ? RED : WHITE);

  if (shape->touch.radian >= 0)
    {
      line.intermediate_points = 0;
      line.coord[0].x = shape->touch.position.x;
      line.coord[0].y = shape->touch.position.y;
      line.coord[1].x = shape->touch.position.x + cos(shape->touch.radian) * 100;
      line.coord[1].y = shape->touch.position.y + sin(shape->touch.radian) * 100;
      bunny_draw_collision_shape
	(&window->buffer, (t_bunny_collision*)&line, rand() | BLACK);
    }

  dot.coord.x = mouse->x;
  dot.coord.y = mouse->y;
  bunny_draw_collision_shape
    (&window->buffer, (t_bunny_collision*)&dot, PINK2);

  bunny_display(window);
  return (GO_ON);
}

int			main(void)
{
  t_shape		*shape;

  assert(window = bunny_start(1440, 900, false, "Collide test"));
  assert(threadpool = bunny_new_threadpool(4));
  assert(elements = bunny_new_pool(1, t_shape));

  shape = bunny_pool_new(elements, t_shape);
  shape->touch.radian = -1;
  shape->col.type = BCT_EQUATION;
  shape->col.equation.coord[0].x = (1440 - 600) / 2;
  shape->col.equation.coord[0].y = (900 - 600) / 2;
  shape->col.equation.coord[1].x = 600;
  shape->col.equation.coord[1].y = 600;

  shape->col.equation.origin_at_center = false;
  shape->col.equation.flipx = false;
  shape->col.equation.flipy = false;

  shape->col.equation.amplitude.x = 10;
  shape->col.equation.amplitude.y = 10;

  shape->col.equation.a = -0.1;
  shape->col.equation.b = 0;
  shape->col.equation.c = 0;

  bunny_clear(&window->buffer, BLACK);
  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_set_display_function(display);
  bunny_loop(window, 25, NULL);
  bunny_delete_pool(elements);
  bunny_delete_threadpool(threadpool);
  bunny_stop(window);
  usleep(1e6);
  return (0);
}
