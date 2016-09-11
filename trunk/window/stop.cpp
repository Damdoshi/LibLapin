// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_stop(t_bunny_window	*window)
{
  struct bunny_window	*win = (struct bunny_window*)window;

  free((void*)win->window_name);
  win->window->close();
  delete win->window;
  delete win;
}
