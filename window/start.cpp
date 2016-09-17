// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		<string>
#include		"lapin_private.h"

t_bunny_window		*bunny_start(unsigned int		width,
				     unsigned int		height,
				     bool			fullscreen,
				     const char			*winname)
{
  return (bunny_start_style(width, height, fullscreen ? FULLSCREEN : DEFAULT_WIN_STYLE, winname));
}

t_bunny_window		*bunny_start_style(unsigned int		width,
					   unsigned int		height,
					   t_bunny_window_style	winstyle,
					   const char		*window_name)
{
  sf::ContextSettings	settings;
  struct bunny_window	*win;
  const char		*str;
  int			i;

#ifdef			__linux__
  if ((str = getenv("DISPLAY")) == NULL || str[0] != ':')
    return (NULL);
  /*
  if (getenv("BUNNY_SELF_TEST") != NULL)
    bunny_self_test();
  */
#endif

  if ((win = new (std::nothrow) bunny_window) == NULL)
    return (NULL);
  if ((win->window = new (std::nothrow) sf::RenderWindow) == NULL)
    {
      delete win;
      return (NULL);
    }

  win->window_name = strdup(window_name);
  win->window->create(sf::VideoMode(width, height, 32), win->window_name, winstyle, settings);
  win->type = WINDOW;
  win->width = width;
  win->height = height;

  for (i = 0; i < LAST_BUNNY_JOYSTICK; ++i)
    if (sf::Joystick::isConnected(i))
      {
	sf::Joystick::Identification	id;
	int				j;

	gl_joystick[i].connected = true;
	gl_joystick[i].name = strdup(id.name.toAnsiString().c_str());
	gl_joystick[i].vendor = id.vendorId;
	gl_joystick[i].product = id.productId;
	gl_joystick[i].nb_button = sf::Joystick::getButtonCount(i);
	gl_joystick[i].axis = 0;
	for (j = 0; j < sf::Joystick::AxisCount; ++j)
	  gl_joystick[i].axis |= (sf::Joystick::hasAxis(i, (sf::Joystick::Axis)j) ? 1 : 0) << j;
      }

  return ((t_bunny_window*)win);
}
