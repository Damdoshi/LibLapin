// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
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

/**
 * @doc-symbol bunny_start
 * @doc-module window
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Open a window and return a structure to handle it.
 * @description If the window is started in fullscreen, then not all sizes are available. Use bunny_get_fullscreen_modes to retrieve the working fullscreen modes for the underlying system.
 * @description The returned structure must be freed with bunny_stop. It is important to call it before exiting, especially in fullscreen, because it restores the original screen resolution if the window opening changed it.
 * @description This function performs a joystick scan. When opening a window, all joysticks will be recognized. After opening the window, connection and disconnection must be handled with events.
 * @description By default, the window is filled with PINK2.
 * @param width The width in pixels of the window to open.
 * @param height The height in pixels of the window to open.
 * @param fullscreen Send true to open the window in fullscreen, false for windowed mode.
 * @param winname The name of the window. It is displayed in the title bar and stored in the t_bunny_window structure.
 * @return-success A pointer to a valid t_bunny_window structure.
 * @return-failure NULL if the window cannot be created.
 * @error BE_UNKNOWN_DISPLAY_DEVICE The display device could not be found or opened.
 * @error BE_CANNOT_OPEN_WINDOW The window could not be created.
 * @log This function writes log entries in the "graphics" and/or "window" log domains when the window creation fails or when the display mode cannot be applied.
 * @see bunny_start_style, bunny_stop, bunny_get_fullscreen_modes, bunny_get_screen_resolution
 *
 * @doc-lang fr
 * @brief Ouvre une fenêtre et renvoie une structure permettant de la manipuler.
 * @description Si la fenêtre est ouverte en plein écran, toutes les tailles ne sont pas disponibles. Utilisez bunny_get_fullscreen_modes pour récupérer les modes plein écran utilisables sur le système sous-jacent.
 * @description La structure renvoyée doit être libérée avec bunny_stop. Il est important de l'appeler avant de quitter, en particulier en plein écran, car cela restaure la résolution d'écran originale si l'ouverture de la fenêtre l'a changée.
 * @description Cette fonction effectue un scan des joysticks. Lors de l'ouverture d'une fenêtre, tous les joysticks sont reconnus. Après l'ouverture, les connexions et déconnexions doivent être gérées avec les événements.
 * @description Par défaut, la fenêtre est remplie avec PINK2.
 * @param width La largeur en pixels de la fenêtre à ouvrir.
 * @param height La hauteur en pixels de la fenêtre à ouvrir.
 * @param fullscreen Envoyez true pour ouvrir la fenêtre en plein écran, false pour le mode fenêtré.
 * @param winname Le nom de la fenêtre. Il est affiché dans la barre de titre et stocké dans la structure t_bunny_window.
 * @return-success Un pointeur vers une structure t_bunny_window valide.
 * @return-failure NULL si la fenêtre ne peut pas être créée.
 * @error BE_UNKNOWN_DISPLAY_DEVICE Le périphérique d'affichage est introuvable ou impossible à ouvrir.
 * @error BE_CANNOT_OPEN_WINDOW La fenêtre n'a pas pu être créée.
 * @log Cette fonction écrit des entrées de log dans les domaines "graphics" et/ou "window" lorsque la création de fenêtre échoue ou lorsque le mode d'affichage ne peut pas être appliqué.
 * @see bunny_start_style, bunny_stop, bunny_get_fullscreen_modes, bunny_get_screen_resolution
 */
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
  win->nwindow = NULL;

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
