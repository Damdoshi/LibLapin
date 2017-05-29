// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

const t_bunny_position			*bunny_get_fullscreen_modes(void)
{
  static t_bunny_position		array[1024 / sizeof(t_bunny_position)] = {0, 0};
  const std::vector<sf::VideoMode>	&modes = sf::VideoMode::getFullscreenModes();
  std::vector
    <sf::VideoMode>::const_iterator	it;
  size_t				i;

  if (array[0].x != 0)
    return (&array[0]);

  for (i = 0, it = modes.begin(); i < 1024 / sizeof(t_bunny_position) && it != modes.end(); ++i, ++it)
    {
      array[i].x = it->width;
      array[i].y = it->height;
    }
  if (it != modes.end())
    --i;
  array[i].x = array[i].y = 0;
  return (&array[0]);
}

