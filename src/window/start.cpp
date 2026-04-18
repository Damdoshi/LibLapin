// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		<string>
#include		"lapin_private.h"

#if			defined(_WIN32)
# define		WIN32_LEAN_AND_MEAN
# include		<windows.h>
#elif			defined(__linux__)
# include		<X11/Xlib.h>
# include		<X11/Xatom.h>
#endif

t_bunny_window		*bunny_start(unsigned int		width,
				     unsigned int		height,
				     bool			fullscreen,
				     const char			*winname)
{
  return (bunny_start_style(width, height, fullscreen ? FULLSCREEN : DEFAULT_WIN_STYLE, winname));
}

void			convert_window(sf::RenderWindow		&window)
{
#if			defined(_WIN32)
  // Généralement inutile : détéction automatique par explorer du pseudo fullscreen.
  // HWND			hwnd = static_cast<HWND>(window.getNativeHandle());

  // SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
#else
  Display		*dpy;

  if ((dpy = XOpenDisplay(NULL)) == NULL)
    return ;

  Window		win = static_cast<Window>(window.getNativeHandle());

  bunny_usleep(100e3);
  XMapRaised(dpy, win);

  Atom			state = XInternAtom(dpy, "_NET_WM_STATE", False);
  Atom			stateval = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
  XEvent		e = {};

  e.type = ClientMessage;
  e.xclient.window = win;
  e.xclient.message_type = state;
  e.xclient.format = 32;
  e.xclient.data.l[0] = 1; // _NET_WM_STATE_ADD
  e.xclient.data.l[1] = stateval;
  e.xclient.data.l[2] = 0;
  e.xclient.data.l[3] = 0;
  e.xclient.data.l[4] = 0;

  Window		root = DefaultRootWindow(dpy);


  XSendEvent(dpy, root, False, SubstructureRedirectMask | SubstructureNotifyMask, &e);
  XFlush(dpy);
  XCloseDisplay(dpy);
#endif
}

#define			PATTERN			\
  "%u width, %u height, %d window style, %s window name -> %p"

t_bunny_window		*bunny_start_style(unsigned int		width,
					   unsigned int		height,
					   t_bunny_window_style	winstyle,
					   const char		*window_name)
{
  hbs::Init		init; (void)init;
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
      settings.antiAliasingLevel = 2;
      win->window->create(sf::VideoMode({width, height}, 32), {win->window_name}, (uint32_t)(winstyle & ~ANTIALIASING), (winstyle & FULLSCREEN) ? sf::State::Fullscreen : sf::State::Windowed, settings);
    }
  else
    win->window->create(sf::VideoMode({width, height}, 32), {win->window_name}, winstyle);
  win->type = WINDOW;
  win->width = width;
  win->height = height;
  win->style = winstyle;
  win->glactive = false;

  // if (winstyle == NO_BORDER)
  // convert_window(*win->window);

  bunny_update_joysticks();
  scream_log_if(PATTERN, "window", width, height, winstyle, window_name, win);
  bunny_fill(&((t_bunny_window*)win)->buffer, PINK2);
  return ((t_bunny_window*)win);
}
