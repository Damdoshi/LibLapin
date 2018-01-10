/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Collide test
*/

#include		<time.h>
#include		<unistd.h>
#include		<lapin.h>
#include		<stdio.h>
#include		<assert.h>

typedef struct		s_shape
{
  t_bunny_collision	col;
  bool			touch;
}			t_shape;

t_bunny_window		*window;
t_bunny_threadpool	*threadpool;
t_bunny_pool		*elements;

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*unused)
{
  (void)unused;
  if (state == GO_UP && sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	loop(void			*unused)
{
  // lel
  void			clear_elements(t_shape		*shape,
				       t_bunny_pool	*pool)
  {
    (void)pool;
    shape->touch = false;
  }
  void			collide_elements(t_shape	*shape,
					 t_bunny_pool	*pool)
  {
    size_t		i;

    for (i = bunny_pool_elem_index(shape) + 1; i < bunny_pool_size(pool); ++i)
      if (bunny_collide(&shape->col, &((t_shape*)pool->data[i])->col))
	{
	  shape->touch = true;
	  ((t_shape*)pool->data[i])->touch = true;
	}
  }

  (void)unused;
  bunny_pool_fast_foreach
    (threadpool, elements, (t_bunny_pool_foreach)clear_elements, elements);
  bunny_pool_fast_foreach
    (threadpool, elements, (t_bunny_pool_foreach)collide_elements, elements);
  return (GO_ON);
}

t_bunny_response	display(void			*unused)
{
  // lel
  void			display_elements(t_shape	*shape,
					 t_bunny_window	*win)
  {
    bunny_draw_collision_shape
      (&win->buffer, &shape->col, shape->touch ? RED : WHITE);
  }

  (void)unused;
  bunny_clear(&window->buffer, BLACK);
  bunny_pool_foreach
    (elements, (t_bunny_pool_foreach)display_elements, window);
  bunny_display(window);
  return (GO_ON);
}

int			main(void)
{
  t_shape		*shape;
  float			angle;
  int			off;

  srand(time(NULL));
  assert(window = bunny_start(1440, 900, false, "Collide test"));
  assert(threadpool = bunny_new_threadpool(4));
  assert(elements = bunny_new_pool(100, t_shape));

  shape = bunny_pool_new(elements, t_shape);
  shape->touch = false;
  shape->col.type = 1; // Circle
  shape->col.circle.coord.x = window->buffer.width / 2;
  shape->col.circle.coord.y = window->buffer.height / 2;
  shape->col.circle.radius = window->buffer.width / 8;

  off = rand() % window->buffer.width / 4 - window->buffer.width / 8;
  angle = rand() % ((int)(2 * M_PI * 10000)) / 10000.0;
  shape = bunny_pool_new(elements, t_shape);
  shape->touch = false;
  shape->col.type = 2; // Line
  shape->col.line.coord[0].x = window->buffer.width / 2 + cos(angle) * window->buffer.height / 4 + off;
  shape->col.line.coord[0].y = window->buffer.height / 2 + sin(angle) * window->buffer.height / 4 + off;
  shape->col.line.coord[1].x = window->buffer.width / 2 + cos(angle + M_PI) * window->buffer.height / 4 + off;
  shape->col.line.coord[1].y = window->buffer.height / 2 + sin(angle + M_PI) * window->buffer.height / 4 + off;
  shape->col.line.intermediate_points = rand() % 5;

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

