// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			"lapin_private.h"

void				bunny_request_focus(const t_bunny_window	*_win)
{
  const struct bunny_window	*win = (const struct bunny_window*)_win;

  win->window->requestFocus();
  scream_log_if("%p", "window", win);
}
