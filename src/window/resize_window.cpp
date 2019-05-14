// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_resize_window(t_bunny_window	*_win,
					    t_bunny_size	pos)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  sf::Vector2u		vec(pos.x, pos.y);

  win->window->setSize(vec);
  win->window->setView(sf::View(sf::FloatRect(0.f, 0.f, pos.x, pos.y)));
  win->width = pos.x;
  win->height = pos.y;
  scream_log_if("%p window, (%d, %d) size", "window", win, pos.x, pos.y);
}

