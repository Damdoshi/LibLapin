
#include <lapin.h>

int main(void)
{
  t_bunny_window *win = bunny_start(800, 600, false, "SCHMOL");
  t_bunny_position pos;
  double x;

  bunny_clear(&win->buffer, BLACK);
  for (x = 0; x < 2 * M_PI; x += M_PI / 32)
    {
      pos.x = 400 + cos(x) * 200;
      pos.y = 300 + sin(x) * 100;
      bunny_set_pixel(&win->buffer, pos, RED);
    }
  bunny_display(win);
  bunny_usleep(1e9 * 10);
  return (0);
}
