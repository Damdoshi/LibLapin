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
  t_shape		*shape;
  t_bunny_position	siz;
  t_bunny_position	off;

  (void)unused;
  off.x = window->buffer.width * 0.2;
  off.y = window->buffer.height * 0.2;
  siz.x = window->buffer.width * 0.8;
  siz.y = window->buffer.height * 0.8;
  if (state == GO_UP && sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (state == GO_UP && sym == BKS_SPACE)
    bunny_pool_clear(elements);
  if (state == GO_DOWN)
    {
      if ((sym >= BKS_F1 && sym < BKS_F1 + LAST_COLLISION_TYPE)
	  || sym == BKS_F8)
	{
	  if ((shape = bunny_pool_new(elements, t_shape)) == NULL)
	    {
	      printf("Maximum element limit reached.\n");
	      return (GO_ON);
	    }
	  shape->touch = false;
	  shape->col.type = sym - BKS_F1;
	}
      if (sym == BKS_F1)
	{
	  shape->col.dot.coord.x = rand() % siz.x + off.x;
	  shape->col.dot.coord.y = rand() % siz.y + off.y;
	}
      else if (sym == BKS_F8)
	{ // Two points at the same position
	  siz.x = rand() % siz.x + off.x;
	  siz.y = rand() % siz.y + off.y;
	  shape->col.type = 0;
	  shape->col.dot.coord.x = siz.x;
	  shape->col.dot.coord.y = siz.y;
	  if ((shape = bunny_pool_new(elements, t_shape)) == NULL)
	    {
	      printf("Maximum element limit reached.\n");
	      return (GO_ON);
	    }
	  shape->touch = false;
	  shape->col.type = 0;
	  shape->col.dot.coord.x = siz.x;
	  shape->col.dot.coord.y = siz.y;
	}
      else if (sym == BKS_F2)
	{
	  shape->col.circle.coord.x = rand() % siz.x + off.x;
	  shape->col.circle.coord.y = rand() % siz.y + off.y;
	  shape->col.circle.radius = rand() % 100 + 20;
	}
      else if (sym == BKS_F3)
	{
	  shape->col.line.coord[0].x = rand() % siz.x + off.x;
	  shape->col.line.coord[0].y = rand() % siz.y + off.y;
	  shape->col.line.coord[1].x = shape->col.line.coord[0].x + rand() % 800 - 400;
	  shape->col.line.coord[1].y = shape->col.line.coord[0].y + rand() % 800 - 400;
	  shape->col.line.intermediate_points = rand() % 5;
	}
      else if (sym == BKS_F4)
	{
	  shape->col.triangle.coord[0].x = rand() % siz.x + off.x;
	  shape->col.triangle.coord[0].y = rand() % siz.y + off.y;
	  shape->col.triangle.coord[1].x = shape->col.triangle.coord[0].x + rand() % 800 - 400;
	  shape->col.triangle.coord[1].y = shape->col.triangle.coord[0].y + rand() % 800 - 400;
	  shape->col.triangle.coord[2].x = shape->col.triangle.coord[0].x + rand() % 800 - 400;
	  shape->col.triangle.coord[2].y = shape->col.triangle.coord[0].y + rand() % 800 - 400;
	}
      else if (sym == BKS_F5)
	{
	  shape->col.rectangular.coord[0].x = rand() % siz.x + off.x / 2;
	  shape->col.rectangular.coord[0].y = rand() % siz.y + off.y / 2;
	  shape->col.rectangular.coord[1].x = rand() % off.x * 4;
	  shape->col.rectangular.coord[1].y = rand() % off.y * 4;
	}
      else if (sym == BKS_F6)
	{
	  shape->col.quad.coord[0].x = rand() % siz.x + off.x;
	  shape->col.quad.coord[0].y = rand() % siz.y + off.y;
	  shape->col.quad.coord[1].x = shape->col.quad.coord[0].x + rand() % 800 - 400;
	  shape->col.quad.coord[1].y = shape->col.quad.coord[0].y + rand() % 800 - 400;
	  shape->col.quad.coord[2].x = shape->col.quad.coord[0].x + rand() % 800 - 400;
	  shape->col.quad.coord[2].y = shape->col.quad.coord[0].y + rand() % 800 - 400;
	  shape->col.quad.coord[3].x = shape->col.quad.coord[0].x + rand() % 800 - 400;
	  shape->col.quad.coord[3].y = shape->col.quad.coord[0].y + rand() % 800 - 400;
	}
      else if (sym == BKS_F7)
	{
	  shape->col.equation.coord[0].x = rand() % siz.x + 50;
	  shape->col.equation.coord[0].y = rand() % siz.y + 50;
	  shape->col.equation.coord[1].x = 300;
	  shape->col.equation.coord[1].y = 300;

	  shape->col.equation.origin_at_center = rand() % 2;
	  shape->col.equation.flipx = rand() % 2;
	  shape->col.equation.flipy = rand() % 2;

	  switch (rand() % 2)
	    {
	    case 0:
	      shape->col.equation.a = 0;
	      shape->col.equation.b = 1;
	      shape->col.equation.c = 0;
	      shape->col.equation.amplitude.x = 1;
	      shape->col.equation.amplitude.y = 1;
	      break ;
	    case 1:
	      shape->col.equation.a = 1;
	      shape->col.equation.b = 0;
	      shape->col.equation.c = 0;
	      shape->col.equation.amplitude.x = 4;
	      shape->col.equation.amplitude.y = 4;
	      break ;
	    }
	}
    }
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
  srand(time(NULL));
  assert(window = bunny_start(1440, 900, false, "Collide test"));
  assert(threadpool = bunny_new_threadpool(4));
  assert(elements = bunny_new_pool(100, t_shape));
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

