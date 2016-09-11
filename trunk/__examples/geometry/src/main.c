
#include		<math.h>
#include		<alloca.h>
#include		<time.h>
#include		<stdlib.h>
#include		"lapin.h"

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*data)
{
  (void)state; (void)data;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int			main(void)
{
  t_bunny_window	*win = bunny_start(800, 600, false, "");
  int			l;
  int			i;

  srand(time(NULL));
  l = (rand() % 2) ? (rand() % 37 + 5) : 5;
  t_bunny_vertex_array	*array = alloca(sizeof(*array) + l * sizeof(t_bunny_vertex));

  bunny_set_key_response(key);
  array->length = l;
  array->vertex[0].pos.x = win->buffer.width / 2;
  array->vertex[0].pos.y = win->buffer.height / 2;
  array->vertex[0].color = rand();
  bunny_clear(&win->buffer, BLACK);
  for (i = 0; i < l - 2; ++i)
    {
      array->vertex[i + 1].pos.x = (1 + cos(((double)i / (l - 2)) * 2.0 * M_PI)) * win->buffer.width / 2;
      array->vertex[i + 1].pos.y = (1 + sin(((double)i / (l - 2)) * 2.0 * M_PI)) * win->buffer.height / 2;
      array->vertex[i + 1].color = rand();
    }
  array->vertex[i + 1].pos.x = array->vertex[1].pos.x;
  array->vertex[i + 1].pos.y = array->vertex[1].pos.y;
  array->vertex[i + 1].color = array->vertex[1].color;
  
  bunny_set_geometry(&win->buffer, BGY_TRIANGLE_FAN, array, NULL);
  bunny_display(win);
  bunny_loop(win, 20, NULL);
  bunny_stop(win);
  return (0);
}

