// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_display(const t_bunny_window	*pic)
{
  struct bunny_window	*win = (struct bunny_window*)pic;

  win->window->display();
}
