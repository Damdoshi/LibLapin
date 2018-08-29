// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_vertical_sync(t_bunny_window	*_win,
					    bool		e)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setVerticalSyncEnabled(e);
}

