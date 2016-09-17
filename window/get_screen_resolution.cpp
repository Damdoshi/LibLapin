// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

const t_bunny_position		*bunny_get_screen_resolution(void)
{
  static t_bunny_position	screen;
  const sf::VideoMode		&mode = sf::VideoMode::getDesktopMode();

  screen.x = mode.width;
  screen.y = mode.height;
  return (&screen);
}

