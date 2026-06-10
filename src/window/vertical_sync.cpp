// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_vertical_sync
 * @doc-kind function
 * @doc-module window
 * @doc-order 350
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Enables or disables vertical synchronization for a window.
 * @description Vertical synchronization synchronizes display refreshes with the screen refresh rate. It is disabled by default.
 * @param window The window whose vertical synchronization flag must be changed.
 * @param enabled Send true to enable vertical synchronization, false to disable it.
 *
 * @doc-lang fr
 * @brief Active ou désactive la synchronisation verticale d'une fenêtre.
 * @description La synchronisation verticale synchronise les rafraîchissements d'affichage avec le taux de rafraîchissement de l'écran. Elle est désactivée par défaut.
 * @param window La fenêtre dont le réglage de synchronisation verticale doit être changé.
 * @param enabled Envoyez true pour activer la synchronisation verticale, false pour la désactiver.
 */
void			bunny_vertical_sync(t_bunny_window	*_win,
					    bool		e)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setVerticalSyncEnabled(e);
}

