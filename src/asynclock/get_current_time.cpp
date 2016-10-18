// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

sf::Clock		gl_bunny_current_time;

double			bunny_get_current_time(void)
{
  sf::Clock		clock;

  return (clock.getElapsedTime().asMicroseconds() / 1e6);
}

