/*
** *****************************************************************************
** damdoshi <damdoshi@blacklatex>
** Ecole 89 - 08/02/2021 02:05:11
**
** - MANDELBROT -
**
** *****************************************************************************
*/

#include	<complex.h>
#include	<lapin.h>

typedef struct s_prog
{
  t_bunny_window *win;
  t_bunny_pixelarray *pix;
  unsigned int	col[256 * 8];
  t_bunny_position click;
  t_bunny_position offset;
  double	zoom;
  float		mandel;
  float		display;
}		t_prog;

t_bunny_response move(const t_bunny_position *ref, void *data)
{
  (void)ref;
  (void)data;
  return (GO_ON);
}

t_bunny_response click(t_bunny_event_state state, t_bunny_mouse_button but, void *data)
{
  t_prog *p = data;

  if (state == GO_UP)
    return (GO_ON);
  if (but != BMB_LEFT)
    return (GO_ON);
  p->click = *bunny_get_mouse_position();
  p->click.x *= 1.0 / p->pix->clipable.scale.x;
  p->click.y *= 1.0 / p->pix->clipable.scale.y;
  return (GO_ON);
}

t_bunny_response wheel(int id, int delta, void*data)
{
  t_prog *p = data;

  (void)id;
  for (int i = 0; i < delta; ++i)
    {
      p->zoom /= 1.1;
      p->offset.x *= 1.1;
      p->offset.y *= 1.1;
    }
  for (int i = 0; i > delta; --i)
    {
      p->zoom *= 1.1;
      p->offset.x /= 1.1;
      p->offset.y /= 1.1;
    }
  return (GO_ON);
}

t_bunny_response loop(void *d)
{
  t_prog *p = d;

  if (bunny_get_mouse_button()[BMB_LEFT])
    {
      t_bunny_position mos = *bunny_get_mouse_position();

      mos.x *= 1.0 / p->pix->clipable.scale.x;
      mos.y *= 1.0 / p->pix->clipable.scale.y;
      p->offset.x += mos.x - p->click.x;
      p->offset.y += mos.y - p->click.y;
      p->click = mos;
    }
  return (GO_ON);
}

t_bunny_response display(void *d)
{
  t_prog *p = d;
  int w = p->pix->clipable.buffer.width;
  int h = p->pix->clipable.buffer.height;

  // memset(p->pix->pixels, 0, w * h * 4);
  for (int y = -h / 2; y < h / 2; ++y)
    {
      for (int x = -w / 2; x < w / 2; ++x)
	{
	  /*
	  float complex c =
	    p->zoom * ((float)(x - p->offset.x) / w)
	    + I * p->zoom * ((float)(y - p->offset.y) / h)
	    ;
	  float complex z = 0;
	  */
	  t_bunny_accurate_position c =
	    {
	     p->zoom * (x - p->offset.x) / w,
	     p->zoom * (y - p->offset.y) / h
	    };
	  t_bunny_accurate_position z = {0, 0};
	  int i;

	  for (i = 0; i < p->display && i < NBRCELL(p->col); ++i)
	    {
	      if (p->mandel > 0)
		{
		  if (p->mandel == 2)
		    {
		      // z = z * z + c;
		      t_bunny_accurate_position new =
			{
			 z.x * z.x - z.y * z.y + c.x,
			 2 * z.x * z.y + c.y
			};
		      z = new;
		    }
		  else
		    {
		      float complex new = z.x + z.y * I;

		      new = cpowf(new, p->mandel) + c.x + c.y * I;
		      z.x = creal(new);
		      z.y = cimag(new);
		    }
		}
	      else
		{
		  // z = (1.0 + I) / cpowf(z, -p->mandel) + c;
		}
	      /*
		if (cabs(z) >= 2)
		break ;
	      */
	      if (z.x * z.x + z.y * z.y >= 4)
		break ;
	    }
	  if (i < p->display)
	    ((unsigned int*)p->pix->pixels)[(x + p->pix->clipable.buffer.width / 2) + (y + p->pix->clipable.buffer.height / 2) * p->pix->clipable.buffer.width] = p->col[i % NBRCELL(p->col)];
	  else
	    ((unsigned int*)p->pix->pixels)[(x + p->pix->clipable.buffer.width / 2) + (y + p->pix->clipable.buffer.height / 2) * p->pix->clipable.buffer.width] = BLACK;
	}
    }
  bunny_blit(&p->win->buffer, &p->pix->clipable, NULL);
  bunny_display(p->win);
  if (0)
    p->display += 1;
  //p->mandel += 0.001;
  return (GO_ON);
}

int main(int argc, char **argv)
{
  static t_prog p;
  int j = 0;
  int w = 300;
  int h = 300;

  if (argc >= 2)
    p.mandel = atof(argv[1]);
  if (argc >= 4)
    {
      w = atoi(argv[2]);
      h = atoi(argv[3]);
    }

  p.win = bunny_start(900, 900, false, "Mandelbrot");
  p.pix = bunny_new_pixelarray(w, h);
  p.mandel = 2;
  p.display = NBRCELL(p.col);
  p.zoom = 16.0;

  p.pix->clipable.scale.x = (double)p.win->buffer.width / w;
  p.pix->clipable.scale.y = (double)p.win->buffer.height / h;
  bunny_enable_full_blit(true);
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = TO_RED(i) | BLACK;
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = RED | TO_BLUE(i) | BLACK;
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = BLUE | TO_RED(255 - i) | BLACK;
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = BLUE | TO_GREEN(i) | BLACK;
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = GREEN | TO_BLUE(255 - i) | BLACK;
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = GREEN | TO_RED(i) | BLACK;
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = RED | TO_GREEN(255 - i) | BLACK;
  for (int i = 0; i < 256 && i < p.display && j < NBRCELL(p.col); ++i)
    p.col[j++] = TO_RED(255 - i) | BLACK;

  for (; j < NBRCELL(p.col); ++j)
    p.col[j] = BLUE | RED;

  bunny_set_display_function(display);
  bunny_set_wheel_response(wheel);
  bunny_set_move_response(move);
  bunny_set_click_response(click);
  bunny_set_loop_main_function(loop);
  bunny_loop(p.win, 25, &p);
  return (0);
}
