
#include		<lapin.h>

void setpixel(void *ptr, int w, int x, int y, int col)
{
  ((char*)ptr)[x + y * w] = col;
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
  unsigned int		cols[256];

  for (size_t i = 0; i < NBRCELL(cols); ++i)
    cols[i] = GRAY(i);

  t_bunny_pixelarray	*pix = bunny_forge_pixelarray
    (win->buffer.width,
     win->buffer.height,
     NULL,
     BBW_256_COLORS,
     false,
     (t_bunny_color*)cols,
     NBRCELL(cols)
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
	  setpixel(pix->pixels, win->buffer.width, i, j, i % NBRCELL(cols));
      bunny_blit(&win->buffer, &pix->clipable, NULL);
      bunny_display(win);

      bunny_usleep(1e4);
      if (pix->color_palette_size > 0)
	pix->color_palette_size -= 1;
      else
	{
	  if (++k > 50)
	    break ;
	}
    }
  bunny_delete_clipable(&pix->clipable);
  bunny_stop(win);
  return (0);
}
