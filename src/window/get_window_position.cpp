// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_get_window_position
 * @doc-kind function
 * @doc-module window
 * @doc-order 330
 * @doc-since 13
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Returns the current position of a window on the desktop.
 * @description The position is expressed in desktop coordinates and corresponds to the window manager position for the top-left corner of the window.
 * @param window The window whose position must be read.
 * @return-case success A t_bunny_position containing the current desktop coordinates of the window.
 * @log Logs are written with the "window" label.
 * @see bunny_move_window
 *
 * @doc-lang fr
 * @brief Renvoie la position courante d'une fenêtre sur le bureau.
 * @description La position est exprimée dans les coordonnées du bureau et correspond à la position du coin supérieur gauche de la fenêtre selon le gestionnaire de fenêtres.
 * @param window La fenêtre dont la position doit être lue.
 * @return-case success Une t_bunny_position contenant les coordonnées courantes de la fenêtre sur le bureau.
 * @log Les logs sont écrits avec l'étiquette "window".
 * @see bunny_move_window
 */
t_bunny_position	bunny_get_window_position(const t_bunny_window	*_win)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  t_bunny_position	pos;
  sf::Vector2i		vec;

  vec = win->window->getPosition();
  pos.x = vec.x;
  pos.y = vec.y;
  scream_log_if("%p window -> (%d, %d)", "window", _win, pos.x, pos.y);
  return (pos);
}

