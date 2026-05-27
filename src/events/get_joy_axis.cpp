// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_joy_axis
 * @doc-module events
 * @doc-kind function
 * @doc-order 220
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the current joystick axis state array.
 * @return-success A pointer to the joystick axis state array.
 * @see t_bunny_joy_axis, bunny_set_joy_axis_response, bunny_set_joy_axis_minimum_offset
 *
 * @doc-lang fr
 * @brief Renvoie le tableau d'état courant des axes de joystick.
 * @return-success Un pointeur vers le tableau d'état des axes de joystick.
 * @see t_bunny_joy_axis, bunny_set_joy_axis_response, bunny_set_joy_axis_minimum_offset
 */
const float		(*bunny_get_joy_axis(void))[LAST_BUNNY_AXIS]
{
  return (gl_joy_axis);
}

