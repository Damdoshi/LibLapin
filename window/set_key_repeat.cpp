// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_set_key_repeat(t_bunny_window	*_win,
					     bool		active)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setKeyRepeatEnabled(active);
}

