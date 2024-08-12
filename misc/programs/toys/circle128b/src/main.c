
#include		<lapin.h>

void setpixel(void *ptr, int w, int x, int y, float *col)
{
  ((float*)ptr)[(x + y * w) * 4 + 0] = col[0];
  ((float*)ptr)[(x + y * w) * 4 + 1] = col[1];
  ((float*)ptr)[(x + y * w) * 4 + 2] = col[2];
  ((float*)ptr)[(x + y * w) * 4 + 3] = col[3];
}

int			main(void)
{
  t_bunny_window	*win = bunny_start(1440, 900, false, "Test");

  t_bunny_pixelarray	*pix = bunny_forge_pixelarray
    (win->buffer.width,
     win->buffer.height,
     NULL,
     BBW_FLOAT_COLORS,
     false,
     NULL,
     0
     );

  bunny_enable_full_blit(true);
  bunny_vertical_sync(win, true);

  int			i;
  int			j;
  int			k;

  k = 0;
  while (1)
    {
      for (j = 0; j < win->buffer.height; ++j)
	for (i = 0; i < win->buffer.width; ++i)
	  {
	    float	col[4] = {0, 0, 0, 0};

	    col[RED_CMP] = 1.0 - (float)i / (win->buffer.width);
	    col[GREEN_CMP] = (float)i / (win->buffer.width);

	    if (j < win->buffer.height / 2)
	      col[ALPHA_CMP] = (float)j / (win->buffer.height / 2);
	    else
	      {
		col[ALPHA_CMP] = 1.0;
		col[BLUE_CMP] = (float)(j - win->buffer.height / 2) / (win->buffer.height / 2);
	      }

	    setpixel(pix->pixels, win->buffer.width, i, j, col);
	  }
      bunny_clear(&win->buffer, BLACK);
      bunny_blit(&win->buffer, &pix->clipable, NULL);
      bunny_display(win);

      bunny_usleep(1e6);
      if (++k < 5)
	{
	  for (size_t i = 0; i < 4; ++i)
	    {
	      size_t tmp = pix->color_shifts[i];
	      size_t rnd = (i + rand() % 3 + 1) % 4;

	      pix->color_shifts[i] = pix->color_shifts[rnd];
	      pix->color_shifts[rnd] = tmp;
	    }
	}
      else break;
    }
  bunny_delete_clipable(&pix->clipable);
  bunny_stop(win);
  return (0);
}
