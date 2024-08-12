
#include		<lapin.h>

void setpixel(void *ptr, int w, int x, int y, int col)
{
  if (col & 1)
    bunny_bitfield_set(ptr, (x + y * w) * 4 + 0);
  else
    bunny_bitfield_clr(ptr, (x + y * w) * 4 + 0);
  if (col & 2)
    bunny_bitfield_set(ptr, (x + y * w) * 4 + 1);
  else
    bunny_bitfield_clr(ptr, (x + y * w) * 4 + 1);
  if (col & 4)
    bunny_bitfield_set(ptr, (x + y * w) * 4 + 2);
  else
    bunny_bitfield_clr(ptr, (x + y * w) * 4 + 2);
  if (col & 8)
    bunny_bitfield_set(ptr, (x + y * w) * 4 + 3);
  else
    bunny_bitfield_clr(ptr, (x + y * w) * 4 + 3);
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
  unsigned int		cols[] =
    {
     BLACK,

     COLOR(255, 255, 0, 0),
     COLOR(255, 128, 0, 0),
     COLOR(255, 0, 255, 0),
     COLOR(255, 0, 128, 0),
     COLOR(255, 0, 0, 255),
     COLOR(255, 0, 0, 128),

     COLOR(255, 255, 255, 0),
     COLOR(255, 128, 128, 0),
     COLOR(255, 0, 255, 255),
     COLOR(255, 0, 128, 128),
     COLOR(255, 255, 0, 255),
     COLOR(255, 128, 0, 128),

     COLOR(255, 70, 70, 70),
     COLOR(255, 150, 150, 150),
     WHITE
    };
  t_bunny_pixelarray	*pix = bunny_forge_pixelarray
    (win->buffer.width,
     win->buffer.height,
     NULL,
     BBW_16_COLORS,
     false,
     (t_bunny_color*)cols,
     NBRCELL(cols)
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
	  setbigpixel(pix->pixels, win->buffer.width, pos.x, pos.y, (int)(1 + (i / (360.0 * 8)) * (NBRCELL(cols) - 1)));
	}
      bunny_blit(&win->buffer, &pix->clipable, NULL);
      bunny_display(win);

      bunny_usleep(1e5);
      if (++k % 5 == 0)
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
