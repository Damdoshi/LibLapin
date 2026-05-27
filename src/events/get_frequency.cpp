// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_frequency
 * @doc-module events
 * @doc-kind function
 * @doc-order 400
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the current main-loop frequency.
 * @return-success The number of loop callback calls requested per second under normal performance conditions.
 * @see bunny_get_delay, bunny_loop, bunny_loop_mw
 *
 * @doc-lang fr
 * @brief Renvoie la fréquence courante de la boucle principale.
 * @return-success Le nombre d'appels au callback de boucle demandés par seconde dans des conditions normales de performances.
 * @see bunny_get_delay, bunny_loop, bunny_loop_mw
 */
int			bunny_get_frequency(void)
{
  return (gl_bunny_frequency);
}

