// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_move_window(t_bunny_window	*_win,
					  t_bunny_position	pos)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  sf::Vector2i		vec(pos.x, pos.y);

  win->window->setPosition(vec);
  auto ppos = win->window->getPosition();
  win->position.x = ppos.x;
  win->position.y = ppos.y;
  scream_log_if("%p window, (%d, %d) position", "window", _win, pos.x, pos.y);
}

