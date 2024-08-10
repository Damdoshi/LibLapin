
#include	<lapin.h>

int		main(void)
{
  t_bunny_window *win = bunny_start(1440, 900, false, "Test");
  t_bunny_picture *pic = bunny_new_picture(win->buffer.width, win->buffer.height);
  unsigned int cola[3] = {RED, GREEN, BLUE};
  unsigned int colb[3] = {TEAL, PURPLE, YELLOW};
  t_bunny_accurate_zposition posa[3] =
    {
     {50, 50, -1},
     {50, win->buffer.height - 50, -1},
     {win->buffer.width - 50, win->buffer.height / 2, 0}
    };
  t_bunny_accurate_zposition posb[3] =
    {
     {300, win->buffer.height / 2, -5},
     {win->buffer.width - 300, 300, 0.2},
     {win->buffer.width - 300, win->buffer.height - 300, 0.2}
    };

  bunny_enable_full_blit(true);
  bunny_clear(&pic->buffer, 0);
  bunny_clear(&win->buffer, BLACK);
  bunny_set_zpolygon(&pic->buffer, &posa[0], cola);
  bunny_set_zpolygon(&win->buffer, &posb[0], colb);
  bunny_blit(&win->buffer, pic, NULL);
  bunny_display(win);
  bunny_loop(win, 50, NULL);
  bunny_delete_clipable(pic);
  bunny_stop(win);
  return (0);
}
