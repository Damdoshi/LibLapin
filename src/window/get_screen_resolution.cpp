// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

const t_bunny_position		*bunny_get_screen_resolution(void)
{
  static t_bunny_position	screen;
  const sf::VideoMode		&mode = sf::VideoMode::getDesktopMode();

  screen.x = mode.width;
  screen.y = mode.height;
  scream_log_if("-> %p(%d, %d)", "system", &screen, screen.x, screen.y);
  return (&screen);
}

