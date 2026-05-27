// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_set_mouse_position_window
 * @doc-kind function
 * @doc-module window
 * @doc-order 260
 * @doc-since 6
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Moves the mouse cursor relatively to a window.
 * @description The coordinates are relative to the top-left corner of the given window.
 * @param window The window used as position reference.
 * @param x The horizontal position where the cursor must be moved.
 * @param y The vertical position where the cursor must be moved.
 * @log Logs are written with the "mouse" and "window" labels.
 *
 * @doc-lang fr
 * @brief Déplace le curseur de la souris relativement à une fenêtre.
 * @description Les coordonnées sont relatives au coin supérieur gauche de la fenêtre donnée.
 * @param window La fenêtre utilisée comme référence de position.
 * @param x La position horizontale où le curseur doit être déplacé.
 * @param y La position verticale où le curseur doit être déplacé.
 * @log Les logs sont écrits avec les étiquettes "mouse" et "window".
 */
void				bunny_set_mouse_position_window(const t_bunny_window	*_win,
								int			x,
								int			y)
{
  const struct bunny_window	*win = (const struct bunny_window*)_win;

  sf::Mouse::setPosition(sf::Vector2i(x, y), *win->window);
  gl_mouse.x = x;
  gl_mouse.y = y;
  scream_log_if("%p window, %d x, %d y", "mouse,window", win, x, y);
}

/**
 * @doc
 * @doc-symbol bunny_set_mouse_position
 * @doc-kind function
 * @doc-module window
 * @doc-order 280
 * @doc-since 6
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Moves the mouse cursor on the desktop.
 * @description The coordinates are relative to the top-left corner of the desktop.
 * @param x The horizontal position where the cursor must be moved.
 * @param y The vertical position where the cursor must be moved.
 * @log Logs are written with the "mouse" label.
 *
 * @doc-lang fr
 * @brief Déplace le curseur de la souris sur le bureau.
 * @description Les coordonnées sont relatives au coin supérieur gauche du bureau.
 * @param x La position horizontale où le curseur doit être déplacé.
 * @param y La position verticale où le curseur doit être déplacé.
 * @log Les logs sont écrits avec l'étiquette "mouse".
 */
void				bunny_set_mouse_position(int				x,
							 int				y)
{
  sf::Mouse::setPosition(sf::Vector2i(x, y));
  gl_mouse.x = x;
  gl_mouse.y = y;
  scream_log_if("%d x, %d y", "mouse", x, y);
}

