//

#include		<assert.h>
#include		<lapin.h>

int			main(int	argc,
			     char	**argv)
{
  t_bunny_window	*win;
  t_bunny_picture	*pic;
  bool			x;

  if (argc != 2 && argc != 3)
    return (1);
  assert((win = bunny_start(800, 600, false, "PSD")));
  assert((pic = bunny_load_picture(argv[1])));
  if (argc == 3)
    x = atoi(argv[2]);
  else
    x = 0;
  if (x == 0)
    bunny_blit(&win->buffer, pic, NULL);
  else
    bunny_blit(&win->buffer, pic, NULL); // Afficher normal
  bunny_display(win);
  bunny_loop(win, 50, NULL);
  bunny_stop(win);
  return (0);
}


