/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_parallax	*pax;

t_bunny_response	move(const t_bunny_position	*ret,
			     void			*unused)
{
  const t_bunny_position *mouse = bunny_get_mouse_position();
  double		x;
  double		y;

  (void)ret;
  (void)unused;
  x = (double)mouse->x / win->buffer.width;
  y = (double)mouse->y / win->buffer.height;
  pax->viewpoint.x = x * pax->inside_size.x;
  pax->viewpoint.y = y * pax->inside_size.y;
  return (GO_ON);
}

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*unused)
{
  (void)unused;
  if (state == GO_UP)
    return (GO_ON);

  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	loop(void			*unused)
{
  (void)unused;
  if (bunny_get_keyboard()[BKS_LEFT])
    pax->viewpoint.x -= 20;
  if (bunny_get_keyboard()[BKS_RIGHT])
    pax->viewpoint.x += 20;
  if (bunny_get_keyboard()[BKS_UP])
    pax->viewpoint.y -= 20;
  if (bunny_get_keyboard()[BKS_DOWN])
    pax->viewpoint.y += 20;
  return (GO_ON);
}

t_bunny_response	display(void			*unused)
{
  (void)unused;
  bunny_clear(&pax->clipable.buffer, BLACK);
  bunny_draw(&pax->clipable);
  bunny_blit(&win->buffer, &pax->clipable, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  assert(win = bunny_begin("./window.dab"));
  if (!(pax = bunny_load_parallax_wh("./parallax.dab", win->buffer.width, win->buffer.height)))
    {
      bunny_perror("bunny_load_tilemap");
      return (EXIT_FAILURE);
    }

  bunny_enable_full_blit(true);
  bunny_set_key_response(key);
  bunny_set_move_response(move);
  bunny_set_loop_main_function(loop);
  bunny_set_display_function(display);

  bunny_loop(win, 25, NULL);

  bunny_delete_clipable(&pax->clipable);
  bunny_end(win);

  return (EXIT_SUCCESS);
}

