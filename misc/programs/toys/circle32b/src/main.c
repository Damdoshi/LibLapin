
#include		<lapin.h>

void setpixel(void *ptr, int w, int x, int y, int col)
{
  ((uint32_t*)ptr)[x + y * w] = col;
}

void setbigpixel(void *ptr, int w, int x, int y, int col)
{
  setpixel(ptr, w, x, y, col);
  setpixel(ptr, w, x - 1, y, col);
  setpixel(ptr, w, x + 1, y, col);
  setpixel(ptr, w, x, y - 1, col);
  setpixel(ptr, w, x, y + 1, col);
  setpixel(ptr, w, x + rand() % 3 - 1, y + rand() % 3 - 1, col);
}

int			main(void)
{
  t_bunny_window	*win = bunny_start(1440, 900, false, "Test");

  t_bunny_pixelarray	*pix = bunny_forge_pixelarray
    (win->buffer.width,
     win->buffer.height,
     NULL,
     BBW_ARGB_COLORS,
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
	    unsigned int v = 0;

	    if (i < win->buffer.width / 2)
	      v |= (int)((1 - (float)i / (win->buffer.width / 2)) * 255) << 0;
	    else
	      v |= (int)(((float)(i - win->buffer.width / 2) / (win->buffer.width / 2)) * 255) << 8;

	    if (j < win->buffer.height / 2)
	      v |= (int)(((float)j / (win->buffer.height / 2)) * 255) << 24;
	    else
	      {
		v |= 255 << 24;
		v |= (int)(((float)(j - win->buffer.height / 2) / (win->buffer.height / 2.0)) * 255) << 16;
	      }

	    setpixel(pix->pixels, win->buffer.width, i, j, v);
	  }
      bunny_clear(&win->buffer, PINK2);
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
