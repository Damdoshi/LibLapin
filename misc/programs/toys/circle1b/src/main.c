
#include		<lapin.h>

int			main(void)
{
  t_bunny_window	*win = bunny_start(1440, 900, false, "Test");
  unsigned int		cols[2] = {WHITE, PINK2};
  t_bunny_pixelarray	*pix = bunny_forge_pixelarray
    (win->buffer.width,
     win->buffer.height,
     NULL,
     BBW_BLACK_AND_WHITE,
     false,
     (t_bunny_color*)cols,
     2
     );

  bunny_vertical_sync(win, true);

  t_bunny_position	pos;
  int			i;
  int			j;
  int			k;

  k = 0;
  while (k < 50)
    {
      for (j = 0; j < win->buffer.height; ++j)
	for (i = 0; i < win->buffer.width; ++i)
	  bunny_bitfield_clr(pix->pixels, i + j * win->buffer.width);
      for (i = 0; i < 360 * 8; ++i)
	{
	  pos.x = cos(2 * M_PI * i / (360 * 8.0)) * win->buffer.width / 3 + win->buffer.width / 2;
	  pos.y = sin(2 * M_PI * i / (360 * 8.0)) * win->buffer.height / 3 + win->buffer.height / 2;
	  bunny_bitfield_set(pix->pixels, pos.x + pos.y * win->buffer.width);
	  bunny_bitfield_set(pix->pixels, pos.x + 1 + pos.y * win->buffer.width);
	  bunny_bitfield_set(pix->pixels, pos.x - 1 + pos.y * win->buffer.width);
	  bunny_bitfield_set(pix->pixels, pos.x + (pos.y + 1) * win->buffer.width);
	  bunny_bitfield_set(pix->pixels, pos.x + (pos.y - 1) * win->buffer.width);
	}
      bunny_blit(&win->buffer, &pix->clipable, NULL);
      bunny_display(win);

      unsigned int tmp = pix->color_palette[0].full;

      pix->color_palette[0].full = pix->color_palette[1].full;
      pix->color_palette[1].full = tmp;
      bunny_usleep(1e5);
      if (++k % 10 == 0)
	{
	  if (pix->color_palette)
	    {
	      pix->color_palette[0].full = rand() | BLACK;
	      pix->color_palette[1].full = ~pix->color_palette[0].full | BLACK;
	    }
	  if (k >= 30)
	    pix->color_palette_size = 1;
	  if (k >= 40)
	    pix->color_palette_size = 0;
	}
    }
  bunny_delete_clipable(&pix->clipable);
  bunny_stop(win);
  return (0);
}
