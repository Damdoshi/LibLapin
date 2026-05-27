// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Biblithèque Lapin

#include			"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_set_mouse_visibility
 * @doc-kind function
 * @doc-module window
 * @doc-order 240
 * @doc-since 6
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Shows or hides the system mouse cursor over a window.
 * @description This function controls the visibility of the system cursor when it moves over the given window.
 * @param window The window whose cursor visibility must be changed.
 * @param visible Send true to show the cursor, false to hide it.
 * @log Logs are written with the "system" and "window" labels.
 *
 * @doc-lang fr
 * @brief Affiche ou masque le curseur système au-dessus d'une fenêtre.
 * @description Cette fonction contrôle la visibilité du curseur système lorsqu'il passe au-dessus de la fenêtre donnée.
 * @param window La fenêtre dont la visibilité du curseur doit être changée.
 * @param visible Envoyez true pour afficher le curseur, false pour le masquer.
 * @log Les logs sont écrits avec les étiquettes "system" et "window".
 */
void				bunny_set_mouse_visibility(const t_bunny_window	*_win,
							   bool			visible)
{
  const struct bunny_window	*win = (const struct bunny_window*)_win;

  win->window->setMouseCursorVisible(visible);
  scream_log_if("%p window, %s visible", "system,window", win, visible ? "true" : "false");
}

