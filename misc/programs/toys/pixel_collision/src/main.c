/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_picture		*pic;
int			i;
int			j;

t_bunny_response	key(t_bunny_event_state	s,
			    t_bunny_keysym	sym,
			    void		*d)
{
  (void)s;
  (void)d;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	display(void		*d)
{
  static const t_bunny_size radius = {2, 2};
  t_bunny_position	pos;

  (void)d;
  if ((i + j) < win->buffer.width * win->buffer.height)
    {
      pos.x = (i + j) % win->buffer.width;
      pos.y = (i + j) / win->buffer.width;
      if (bunny_pixel_collision(pic, &pos, 0.2))
	bunny_set_disk(&win->buffer, pos, radius, ALPHA(128, RED), BLACK, 1);
      i += 30;
    }
  else
    {
      j += 5;
      i = j;
    }
  bunny_display(win);
  return (GO_ON);
}

int			main(int		argc,
			     char		**argv)
{
  assert(argc == 2);
  assert(pic = bunny_load_picture(argv[1]));
  assert(win = bunny_start
	 (pic->buffer.width, pic->buffer.height, false, "The Pixel Collision test"));
  bunny_set_key_response(key);
  bunny_set_display_function(display);

  bunny_clear(&win->buffer, BLACK);
  bunny_blit(&win->buffer, pic, NULL);
  i = 0;
  j = 0;
  bunny_display(win);
  bunny_loop(win, 50, NULL);
  bunny_delete_clipable(pic);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

