// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_position	bunny_get_window_position(const t_bunny_window	*_win)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  t_bunny_position	pos;
  sf::Vector2i		vec;

  vec = win->window->getPosition();
  pos.x = vec.x;
  pos.y = vec.y;
  scream_log_if("%p window -> (%d, %d)", "window", _win, pos.x, pos.y);
  return (pos);
}

