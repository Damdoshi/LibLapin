// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_stop(t_bunny_window	*window)
{
  size_t		oldptr = (size_t)window; // To avoid warning about use after free
  struct bunny_window	*win = (struct bunny_window*)window;

  bunny_free((void*)win->window_name);
  win->window->close();
  delete win->window;
  delete win;
  scream_log_if("%zu", "window", oldptr);
}
