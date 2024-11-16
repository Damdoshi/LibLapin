/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
**
** LibLapin Test
*/

#include		<lapin.h>

t_bunny_window		*win;
t_bunny_waterbox	*wbox;

t_bunny_response	loop(void		*ptr)
{
  (void)ptr;
  bunny_waterbox(wbox);
  return (GO_ON);
}

t_bunny_response	display(void		*ptr)
{
  (void)ptr;
  bunny_clear(&win->buffer, BLACK);
  bunny_waterbox_blit(&win->buffer, wbox, BWS_HORIZONTAL, -1);
  bunny_display(win);
  return (GO_ON);
}

int			main(int		argc,
			     char		**argv)
{
  if (argc != 2)
    return (1);
  win = bunny_start(800, 600, false, "WaterBox");
  wbox = bunny_load_waterbox(argv[1]);
  if (!win || !wbox)
    return (1);
  bunny_set_display_function(display);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 25, NULL);
  bunny_delete_waterbox(wbox);
  bunny_stop(win);
  return (0);
}

