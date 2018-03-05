#include <lapin.h>  // For all bunny_ things.o
#include <unistd.h> // For usleep
#include <stdlib.h> // For EXIT_SUCCESS

int main(void)
{
  t_bunny_window *win = bunny_start(800, 600, false, "Open a window tutorial");

  bunny_display(win);
  usleep(1e6);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
