// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_set_joystick_threshold
 * @doc-module events
 * @doc-kind function
 * @doc-order 215
 * @doc-since 13
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Sets the backend joystick movement threshold for a window.
 * @param win The window whose backend threshold must be changed.
 * @param offset The minimum joystick movement required by the backend to produce an event.
 * @see bunny_set_joy_axis_minimum_offset, t_bunny_joy_axis
 *
 * @doc-lang fr
 * @brief Règle le seuil de mouvement joystick du moteur sous-jacent pour une fenêtre.
 * @param win La fenêtre dont le seuil sous-jacent doit être changé.
 * @param offset Le mouvement minimal de joystick requis par le moteur sous-jacent pour produire un événement.
 * @see bunny_set_joy_axis_minimum_offset, t_bunny_joy_axis
 */
void		bunny_set_joystick_threshold(t_bunny_window	*_win,
					     float		offset)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setJoystickThreshold(offset);
}
