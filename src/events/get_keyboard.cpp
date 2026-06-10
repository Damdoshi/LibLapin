// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_keyboard
 * @doc-module events
 * @doc-kind function
 * @doc-order 50
 * @doc-since 2
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the current keyboard state array.
 * @return-success A pointer to the keyboard state array, where true means down and false means up.
 * @see t_bunny_key, bunny_set_key_response
 *
 * @doc-lang fr
 * @brief Renvoie le tableau d'état courant du clavier.
 * @return-success Un pointeur vers le tableau d'état du clavier, où true signifie enfoncé et false relâché.
 * @see t_bunny_key, bunny_set_key_response
 */
const bool		*bunny_get_keyboard(void)
{
  return (gl_keyboard);
}
