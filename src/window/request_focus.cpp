// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_request_focus
 * @doc-kind function
 * @doc-module window
 * @doc-order 300
 * @doc-since 6
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Asks the window manager to give focus to a window.
 * @description The system or window manager may refuse the request, especially if focus stealing prevention is enabled.
 * @param window The window that requests focus.
 * @log Logs are written with the "window" label.
 *
 * @doc-lang fr
 * @brief Demande au gestionnaire de fenêtres de donner le focus à une fenêtre.
 * @description Le système ou le gestionnaire de fenêtres peut refuser la demande, en particulier si la prévention du vol de focus est activée.
 * @param window La fenêtre qui demande le focus.
 * @log Les logs sont écrits avec l'étiquette "window".
 */
void				bunny_request_focus(const t_bunny_window	*_win)
{
  const struct bunny_window	*win = (const struct bunny_window*)_win;

  win->window->requestFocus();
  scream_log_if("%p", "window", win);
}
