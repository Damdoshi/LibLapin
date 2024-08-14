
#include		<lapin.h>

void setpixel(uint8_t *ptr, int w, int h, int x, int y, int col, int bpp)
{
  size_t plansize = w * h;

  plansize += plansize % 8 ? (8 - plansize % 8) : 0;
  plansize *= bpp / 8.0;
  for (int i = 0; i < bpp; ++i)
    {
      if ((col >> i) & 1)
	bunny_bitfield_set(&ptr[plansize * i], (x + y * w));
      else
	bunny_bitfield_clr(&ptr[plansize * i], (x + y * w));
    }
}

void setbigpixel(void *ptr, int w, int h, int x, int y, int col, int bpp)
{
  setpixel(ptr, w, h, x, y, col, bpp);
  setpixel(ptr, w, h, x - 1, y, col, bpp);
  setpixel(ptr, w, h, x + 1, y, col, bpp);
  setpixel(ptr, w, h, x, y - 1, col, bpp);
  setpixel(ptr, w, h, x, y + 1, col, bpp);
  setpixel(ptr, w, h, x + rand() % 3 - 1, y + rand() % 3 - 1, col, bpp);
}

void			rotcol(t_bunny_pixelarray	*pix)
{
  t_bunny_color		tmp = {.full = pix->color_palette[0].full};
  int			i;

  for (i = 0; i < pix->color_palette_size - 1; ++i)
    pix->color_palette[i].full = pix->color_palette[i + 1].full;
  pix->color_palette[i].full = tmp.full;
}

int			main(void)
{
  t_bunny_window	*win = bunny_start(1440, 900, false, "Test");
  unsigned int		cols[16];
  for (size_t i = 0; i < NBRCELL(cols); ++i)
    cols[i] = GRAY(((float)i / NBRCELL(cols)) * 255);
  int			bpp;
  t_bunny_pixelarray	*pix = bunny_forge_pixelarray
    (win->buffer.width,
     win->buffer.height,
     NULL,
     bpp = 4,
     true,
     (t_bunny_color*)cols,
     NBRCELL(cols)
     );

  // bunny_vertical_sync(win, true);
  bunny_enable_full_blit(true);

  t_bunny_position	pos;
  int			i;
  int			j;
  int			k;

  k = 0;
  while (1)
    {
      for (j = 0; j < win->buffer.height; ++j)
	for (i = 0; i < win->buffer.width; ++i)
	  setpixel(pix->pixels, win->buffer.width, win->buffer.height, i, j, 0, bpp);
      for (i = 0; i < 360 * 8; ++i)
	{
	  pos.x = cos(2 * M_PI * i / (360 * 8.0)) * win->buffer.width / 3 + win->buffer.width / 2;
	  pos.y = sin(2 * M_PI * i / (360 * 8.0)) * win->buffer.height / 3 + win->buffer.height / 2;
	  setbigpixel(pix->pixels, win->buffer.width, win->buffer.height, pos.x, pos.y, (int)((i / (360.0 * 8)) * NBRCELL(cols)), bpp);
	}
      bunny_blit(&win->buffer, &pix->clipable, NULL);
      bunny_display(win);

      rotcol(pix);
      // bunny_usleep(1e4);
      if (++k % 20 == 0)
	{
	  if (pix->color_palette_size > 0)
	    pix->color_palette_size -= 1;
	  else
	    break ;
	}
    }
  bunny_delete_clipable(&pix->clipable);
  bunny_stop(win);
  return (0);
}
