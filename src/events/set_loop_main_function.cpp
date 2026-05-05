// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_loop_main_function
 * @doc-module events
 * @doc-kind function
 * @doc-order 370
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Registers the fixed-frequency main-loop callback.
 * @param lop The callback to call at the frequency requested by bunny_loop or bunny_loop_mw.
 * @see t_bunny_loop, bunny_loop, bunny_loop_mw
 *
 * @doc-lang fr
 * @brief Enregistre le callback de boucle principale à fréquence fixe.
 * @param lop Le callback à appeler à la fréquence demandée par bunny_loop ou bunny_loop_mw.
 * @see t_bunny_loop, bunny_loop, bunny_loop_mw
 */
void			bunny_set_loop_main_function(t_bunny_loop	loop)
{
  gl_callback.loop = loop;
}

