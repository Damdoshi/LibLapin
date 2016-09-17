// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_resize_window(t_bunny_window	*_win,
					    t_bunny_size	pos)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  sf::Vector2u		vec(pos.x, pos.y);
  
  win->window->setSize(vec);
  win->width = pos.x;
  win->height = pos.y;
}

