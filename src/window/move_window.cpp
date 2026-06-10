// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_move_window
 * @doc-kind function
 * @doc-module window
 * @doc-order 320
 * @doc-since 9
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Asks the system to move a window on the desktop.
 * @description The position is expressed in desktop coordinates. The window manager may adjust or refuse the requested position depending on the platform and user configuration.
 * @param window The window to move.
 * @param position The requested position for the top-left corner of the window.
 * @log Logs are written with the "window" label.
 * @see bunny_get_window_position
 *
 * @doc-lang fr
 * @brief Demande au système de déplacer une fenêtre sur le bureau.
 * @description La position est exprimée dans les coordonnées du bureau. Le gestionnaire de fenêtres peut ajuster ou refuser la position demandée selon la plate-forme et la configuration utilisateur.
 * @param window La fenêtre à déplacer.
 * @param position La position demandée pour le coin supérieur gauche de la fenêtre.
 * @log Les logs sont écrits avec l'étiquette "window".
 * @see bunny_get_window_position
 */
void			bunny_move_window(t_bunny_window	*_win,
					  t_bunny_position	pos)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  sf::Vector2i		vec(pos.x, pos.y);

  win->window->setPosition(vec);
  auto ppos = win->window->getPosition();
  win->position.x = ppos.x;
  win->position.y = ppos.y;
  scream_log_if("%p window, (%d, %d) position", "window", _win, pos.x, pos.y);
}

