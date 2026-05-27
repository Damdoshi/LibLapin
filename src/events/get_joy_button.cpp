// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_joy_button
 * @doc-module events
 * @doc-kind function
 * @doc-order 250
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the current joystick button state array.
 * @return-success A pointer to the joystick button state array.
 * @see t_bunny_joy_button, bunny_set_joy_button_response
 *
 * @doc-lang fr
 * @brief Renvoie le tableau d'état courant des boutons de joystick.
 * @return-success Un pointeur vers le tableau d'état des boutons de joystick.
 * @see t_bunny_joy_button, bunny_set_joy_button_response
 */
const bool		(*bunny_get_joy_button(void))[LAST_BUNNY_BUTTON]
{
  return (gl_joy_button);
}

