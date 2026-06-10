// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_display
 * @doc-kind function
 * @doc-module window
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Refreshes the window content on screen.
 * @description Call this function after drawing into a window to make the result appear on screen.
 * @param window The window to display and refresh on screen.
 * @log Logs are written with the "window" and "graphics" labels.
 * @see bunny_blit, t_bunny_window
 *
 * @doc-lang fr
 * @brief Rafraîchit le contenu de la fenêtre à l'écran.
 * @description Appelez cette fonction après avoir dessiné dans une fenêtre afin de faire apparaître le résultat à l'écran.
 * @param window La fenêtre à afficher et rafraîchir à l'écran.
 * @log Les logs sont écrits avec les étiquettes "window" et "graphics".
 * @see bunny_blit, t_bunny_window
 */
void			bunny_display(const t_bunny_window	*pic)
{
  struct bunny_window	*win = (struct bunny_window*)pic;

  win->window->display();
  scream_log_if("%p", "window,graphics", pic);
}

