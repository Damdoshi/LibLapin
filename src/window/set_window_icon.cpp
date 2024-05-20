// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// Lapin library

#include		"lapin_private.h"

void			bunny_set_window_icon(t_bunny_window		*_win,
					      t_bunny_pixelarray	*px)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setIcon
    (px->clipable.buffer.width,
     px->clipable.buffer.height,
     (const sf::Uint8*)px->pixels);
}

