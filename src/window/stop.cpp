// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_stop
 * @doc-kind function
 * @doc-module window
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Destroys a window opened by LibLapin.
 * @description This function closes the underlying system window, releases the window name and destroys the t_bunny_window structure. If the window changed the screen resolution when it was opened, the system is expected to restore the previous mode.
 * @param window The window to destroy.
 * @log Logs are written with the "window" label.
 * @see bunny_start, bunny_start_style
 *
 * @doc-lang fr
 * @brief Détruit une fenêtre ouverte par la LibLapin.
 * @description Cette fonction ferme la fenêtre système sous-jacente, libère le nom de la fenêtre et détruit la structure t_bunny_window. Si la fenêtre a changé la résolution de l'écran lors de son ouverture, le système est censé restaurer le mode précédent.
 * @param window La fenêtre à détruire.
 * @log Les logs sont écrits avec l'étiquette "window".
 * @see bunny_start, bunny_start_style
 */
void			bunny_stop(t_bunny_window	*window)
{
  size_t		oldptr = (size_t)window; // To avoid warning about use after free
  struct bunny_window	*win = (struct bunny_window*)window;

  bunny_free((void*)win->window_name);
  win->window->close();
  delete win->window;
  delete win;
  scream_log_if("%zu", "window", oldptr);
}
