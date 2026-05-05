// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_window
 * @doc-module events
 * @doc-kind function
 * @doc-order 335
 * @doc-since 6
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the window currently producing an event.
 * @return-success The window that is currently being processed.
 * @see bunny_loop, bunny_loop_mw
 *
 * @doc-lang fr
 * @brief Renvoie la fenêtre qui produit l'événement courant.
 * @return-success La fenêtre actuellement en cours de traitement.
 * @see bunny_loop, bunny_loop_mw
 */
const t_bunny_window	*bunny_get_window(void)
{
  return (gl_window);
}

