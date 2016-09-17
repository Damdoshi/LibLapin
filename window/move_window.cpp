// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_move_window(t_bunny_window	*_win,
					  t_bunny_position	pos)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  sf::Vector2i		vec(pos.x, pos.y);
  
  win->window->setPosition(vec);
}

