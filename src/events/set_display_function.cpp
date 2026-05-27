// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_display_function
 * @doc-module events
 * @doc-kind function
 * @doc-order 350
 * @doc-since 7
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Registers the display callback.
 * @param display The callback to call when the loop decides that display should be refreshed.
 * @see t_bunny_display, bunny_loop, bunny_loop_mw
 *
 * @doc-lang fr
 * @brief Enregistre le callback d'affichage.
 * @param display Le callback à appeler lorsque la boucle décide que l'affichage doit être rafraîchi.
 * @see t_bunny_display, bunny_loop, bunny_loop_mw
 */
void			bunny_set_display_function(t_bunny_display	display)
{
  gl_callback.display = display;
}

