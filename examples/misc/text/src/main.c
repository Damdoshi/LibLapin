/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#include			<lapin.h>

int				main(void)
{
  t_bunny_window		*win = bunny_start(800, 600, false, "Text with LibLapin");
  t_bunny_position		size = {10, 14};
  t_bunny_font			*gfx = bunny_load_gfx_font("./font.png", &size);
  t_bunny_font			*ttf = bunny_load_ttf_font("./font.ttf");


  gfx->clipable.color_mask.full = BLACK;
  bunny_clear(&win->buffer, PINK2);

  gfx->string = "This uses a png font";
  ttf->string = "This uses a ttf font";

  size.y = 200;
  bunny_blit(&win->buffer, &gfx->clipable, &size);

  size.y = 400;
  bunny_blit(&win->buffer, &ttf->clipable, &size);

  bunny_display(win);
  bunny_loop(win, 25, NULL);

  bunny_delete_clipable(&gfx->clipable);
  bunny_delete_clipable(&ttf->clipable);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

