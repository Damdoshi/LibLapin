// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_mouse_button
 * @doc-module events
 * @doc-kind function
 * @doc-order 100
 * @doc-since 2
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the current mouse button state array.
 * @return-success A pointer to the mouse button state array, where true means down and false means up.
 * @see t_bunny_click, bunny_set_click_response
 *
 * @doc-lang fr
 * @brief Renvoie le tableau d'état courant des boutons de souris.
 * @return-success Un pointeur vers le tableau d'état des boutons de souris, où true signifie enfoncé et false relâché.
 * @see t_bunny_click, bunny_set_click_response
 */
const bool		*bunny_get_mouse_button(void)
{
  return (gl_button);
}
