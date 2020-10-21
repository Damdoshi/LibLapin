// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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

#define			PATTERN			\
  "%u width, %u height, %d window style, %s window name -> %p"

t_bunny_window		*bunny_start_style(unsigned int		width,
					   unsigned int		height,
					   t_bunny_window_style	winstyle,
					   const char		*window_name)
{
  sf::ContextSettings	settings;
  struct bunny_window	*win;
  const char		*str;

#ifdef			__linux__
  if ((str = getenv("DISPLAY")) == NULL || strchr(str, ':') == NULL)
    scream_error_if(return (NULL), BE_UNKNOWN_DISPLAY_DEVICE, PATTERN, "window",
		    width, height, winstyle, window_name, (void*)NULL);
#endif

  if ((win = new (std::nothrow) bunny_window) == NULL)
    scream_error_if(return (NULL), ENOMEM, PATTERN, "window",
		    width, height, winstyle, window_name, (void*)NULL);
  if ((win->window = new (std::nothrow) sf::RenderWindow) == NULL)
    {
      delete win;
      scream_error_if(return (NULL), ENOMEM, PATTERN, "window",
		      width, height, winstyle, window_name, (void*)NULL);
    }

  win->window_name = bunny_strdup(window_name);
  if (winstyle & ANTIALIASING)
    {
      settings.antialiasingLevel = 2;
      win->window->create(sf::VideoMode(width, height, 32), win->window_name, winstyle & ~ANTIALIASING, settings);
    }
  else
    win->window->create(sf::VideoMode(width, height, 32), win->window_name, winstyle);
  win->type = WINDOW;
  win->width = width;
  win->height = height;
  win->style = winstyle;

  bunny_update_joysticks();
  scream_log_if(PATTERN, "window", width, height, winstyle, window_name, win);
  bunny_fill(&((t_bunny_window*)win)->buffer, PINK2);
  return ((t_bunny_window*)win);
}
