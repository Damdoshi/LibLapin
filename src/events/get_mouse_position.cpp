// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_mouse_position
 * @doc-module events
 * @doc-kind function
 * @doc-order 130
 * @doc-since 2
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the last known mouse position.
 * @return-success A pointer to the current mouse position structure.
 * @see t_bunny_move, bunny_set_move_response
 *
 * @doc-lang fr
 * @brief Renvoie la dernière position connue de la souris.
 * @return-success Un pointeur vers la structure de position courante de la souris.
 * @see t_bunny_move, bunny_set_move_response
 */
const t_bunny_position	*bunny_get_mouse_position(void)
{
  return (&gl_mouse);
}
