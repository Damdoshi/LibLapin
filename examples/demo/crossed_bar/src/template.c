/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2015
**
** The Lapin Noir Demo for LibLapin1.6
*/

#include		<lapin.h>
#include		<math.h>
#include		<stdio.h>
#include		<assert.h>

#define			NORM(a, b)		(sqrt((a * a) + (b * b)))

t_bunny_window		*win;
t_bunny_picture		*pic[2];
t_bunny_picture		*bunny;
double			rotation = 0;
double			scale = 0;
double			scale2 = 0;

static void		reset(t_bunny_picture	*pic)
{
  pic->clip_x_position = 0;
  pic->clip_y_position = 0;
  pic->clip_width = pic->buffer.width;
  pic->clip_height = pic->buffer.height;
}

static void		square(t_bunny_picture	*pic,
			       int		x,
			       int		y,
			       int		w,
			       int		h,
			       unsigned int	c)
{
  pic->clip_x_position = x;
  pic->clip_y_position = y;
  pic->clip_width = w;
  pic->clip_height = h;
  bunny_fill(&pic->buffer, c);
}

static t_bunny_response	loop(void		*data)
{
  t_bunny_position	pos;
  t_bunny_position	mid;

  (void)data;
  bunny_fill(&win->buffer, ALPHA(32, BLACK));
  pos.x = win->buffer.width / 2;
  pos.y = win->buffer.height / 2;
  pic[0]->rotation = rotation;
  pic[1]->rotation = -(rotation + cos(8 * rotation * M_PI / 180.0));
  
  pic[0]->scale.x = 2 + cos(scale * M_PI / 180.0);
  pic[0]->scale.y = 2 + cos(scale * M_PI / 180.0);
  pic[1]->scale.x = 2.2 + sin(scale2 * M_PI / 180.0);
  pic[1]->scale.y = 2.2 + sin(scale2 * M_PI / 180.0);
  rotation += 1;
  scale += 2;
  scale2 -= 1;
  mid.x = win->buffer.width / 2;
  mid.y = win->buffer.height / 2;
  bunny->rotation = -rotation * 2;
  bunny->scale.x = 2 - cos(scale * M_PI / 180.0);
  bunny->scale.y = 2 + sin(scale * M_PI / 180.0);
  bunny_blit(&win->buffer, pic[0], &pos);
  bunny_blit(&win->buffer, bunny, &mid);
  bunny_blit(&win->buffer, pic[1], &pos);
  bunny_display(win);
  bunny_set_mouse_position_window(win, win->buffer.width / 2, win->buffer.height / 2);
  return (GO_ON);
}

static t_bunny_response	key(t_bunny_event_state	state,
			    t_bunny_keysym	keysym,
			    void		*data)
{
  (void)state;
  (void)data;
  if (keysym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (keysym >= BKS_0 && keysym <= BKS_9)
    printf("%d\n",  keysym - BKS_0);
  return (GO_ON);
}

int			main(void)
{
  int			w;
  int			i;

  assert((win = bunny_start(800, 600, false, "The Lapins Noirs")) != NULL);
  assert((pic[0] = bunny_new_picture(NORM(800, 600), NORM(800, 600))) != NULL);
  assert((pic[1] = bunny_new_picture(NORM(800, 600), NORM(800, 600))) != NULL);
  assert((bunny = bunny_load_picture("bigbunny.png")) != NULL);

  bunny->origin.x = bunny->buffer.width / 2;
  bunny->origin.y = bunny->buffer.height / 2;
  pic[0]->origin.x = pic[0]->buffer.width / 2;
  pic[0]->origin.y = pic[0]->buffer.height / 2;
  pic[1]->origin.x = pic[1]->buffer.width / 2;
  pic[1]->origin.y = pic[1]->buffer.height / 2;
  bunny_clear(&pic[0]->buffer, 0);
  bunny_clear(&pic[1]->buffer, 0);
  for (i = 0, w = 50; i < pic[0]->buffer.width; i += 100)
    {
      square(pic[0], i, 0, w, pic[0]->buffer.height, ALPHA(150, rand()));
      square(pic[1], i, 0, w, pic[1]->buffer.height, ALPHA(150, rand()));
    }
  reset(pic[0]);
  reset(pic[1]);
  bunny_set_loop_main_function(loop);
  bunny_set_key_response(key);
  bunny_loop(win, 50, NULL);
  bunny_delete_clipable(pic[0]);
  bunny_delete_clipable(pic[1]);
  bunny_stop(win);
  return (EXIT_FAILURE);
}

