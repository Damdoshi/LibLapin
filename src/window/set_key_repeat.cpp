// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_set_key_repeat
 * @doc-kind function
 * @doc-module window
 * @doc-order 220
 * @doc-since 6
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Enables or disables keyboard repetition for a window.
 * @description Keyboard repetition is useful for text input. It is not a keydown state and should usually be disabled in games. Use bunny_get_keyboard when you need the current keyboard state.
 * @param window The window whose key repetition policy must be modified.
 * @param repeat Send true to enable key repetition, false to disable it.
 * @log Logs are written with the "system" and "window" labels.
 * @see bunny_get_keyboard
 *
 * @doc-lang fr
 * @brief Active ou désactive la répétition clavier pour une fenêtre.
 * @description La répétition clavier est utile pour la saisie de texte. Ce n'est pas un état de touche maintenue et elle devrait généralement être désactivée dans les jeux. Utilisez bunny_get_keyboard si vous avez besoin de l'état courant du clavier.
 * @param window La fenêtre dont la politique de répétition clavier doit être modifiée.
 * @param repeat Envoyez true pour activer la répétition clavier, false pour la désactiver.
 * @log Les logs sont écrits avec les étiquettes "system" et "window".
 * @see bunny_get_keyboard
 */
void			bunny_set_key_repeat(t_bunny_window	*_win,
					     bool		active)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setKeyRepeatEnabled(active);
  scream_log_if("%p window, %s active", "system,window", win, active ? "true" : "false");
}

