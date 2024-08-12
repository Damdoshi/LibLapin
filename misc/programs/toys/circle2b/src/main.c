
#include		<lapin.h>

void setpixel(void *ptr, int w, int x, int y, int col)
{
  if (col & 1)
    bunny_bitfield_set(ptr, (x + y * w) * 2 + 0);
  else
    bunny_bitfield_clr(ptr, (x + y * w) * 2 + 0);
  if (col & 2)
    bunny_bitfield_set(ptr, (x + y * w) * 2 + 1);
  else
    bunny_bitfield_clr(ptr, (x + y * w) * 2 + 1);
}

void setbigpixel(void *ptr, int w, int x, int y, int col)
{
  setpixel(ptr, w, x + rand() % 3 - 1, y + rand() % 3 - 1, col);
}

int			main(void)
{
  t_bunny_window	*win = bunny_start(1440, 900, false, "Test");
  unsigned int		cols[] = {BLACK, RED, GREEN, BLUE};
  t_bunny_pixelarray	*pix = bunny_forge_pixelarray
    (win->buffer.width,
     win->buffer.height,
     NULL,
     BBW_4_COLORS,
     false,
     (t_bunny_color*)cols,
     4
     );

  bunny_vertical_sync(win, true);

  t_bunny_position	pos;
  int			i;
  int			j;
  int			k;

  k = 0;
  while (1)
    {
      for (j = 0; j < win->buffer.height; ++j)
	for (i = 0; i < win->buffer.width; ++i)
	  setpixel(pix->pixels, win->buffer.width, i, j, 0);
      for (i = 0; i < 360 * 8; ++i)
	{
	  pos.x = cos(2 * M_PI * i / (360 * 8.0)) * win->buffer.width / 3 + win->buffer.width / 2;
	  pos.y = sin(2 * M_PI * i / (360 * 8.0)) * win->buffer.height / 3 + win->buffer.height / 2;
	  if (i < 360 * 8 * 1 / 3)
	    setbigpixel(pix->pixels, win->buffer.width, pos.x, pos.y, 1);
	  else if (i < 360 * 8 * 2 / 3)
	    setbigpixel(pix->pixels, win->buffer.width, pos.x, pos.y, 2);
	  else
	    setbigpixel(pix->pixels, win->buffer.width, pos.x, pos.y, 3);
	}
      bunny_blit(&win->buffer, &pix->clipable, NULL);
      bunny_display(win);

      bunny_usleep(1e4);
      if (++k % 100 == 0)
	{
	  // for (unsigned char c = 0; c < pix->color_palette_size; ++c)
	  // pix->color_palette[c].full = rand() | BLACK;
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
