// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_position	bunny_get_screen_size(void)
{
  t_bunny_position	s;

  s.x = sf::VideoMode::getDesktopMode().width;
  s.y = sf::VideoMode::getDesktopMode().height;
  return (s);
}

