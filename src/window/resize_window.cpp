// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_resize_window
 * @doc-kind function
 * @doc-module window
 * @doc-order 340
 * @doc-since 9
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Resizes a window.
 * @description The render view is reset to match the new size. The window manager may adjust or refuse the requested size depending on the platform and user configuration.
 * @param window The window to resize.
 * @param size The new size of the window.
 * @log Logs are written with the "window" label.
 *
 * @doc-lang fr
 * @brief Redimensionne une fenêtre.
 * @description La vue de rendu est réinitialisée pour correspondre à la nouvelle taille. Le gestionnaire de fenêtres peut ajuster ou refuser la taille demandée selon la plate-forme et la configuration utilisateur.
 * @param window La fenêtre à redimensionner.
 * @param size La nouvelle taille de la fenêtre.
 * @log Les logs sont écrits avec l'étiquette "window".
 */
void			bunny_resize_window(t_bunny_window	*_win,
					    t_bunny_size	pos)
{
  struct bunny_window	*win = (struct bunny_window*)_win;
  sf::Vector2u		vec(pos.x, pos.y);

  win->window->setSize(vec);
  win->window->setView(sf::View(sf::FloatRect({0.f, 0.f}, {pos.x, pos.y})));
  win->width = pos.x;
  win->height = pos.y;
  auto ppos = win->window->getPosition();
  win->position.x = ppos.x;
  win->position.y = ppos.y;
  scream_log_if("%p window, (%d, %d) size", "window", win, pos.x, pos.y);
}

