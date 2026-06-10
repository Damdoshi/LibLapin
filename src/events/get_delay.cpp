// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_delay
 * @doc-module events
 * @doc-kind function
 * @doc-order 405
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the duration of one main-loop tick in seconds.
 * @return-success The theoretical duration, in seconds, between two calls to the loop callback.
 * @see bunny_get_frequency, bunny_loop
 *
 * @doc-lang fr
 * @brief Renvoie la durée d'un tour de boucle principale en secondes.
 * @return-success La durée théorique, en secondes, entre deux appels au callback de boucle.
 * @see bunny_get_frequency, bunny_loop
 */
double			bunny_get_delay(void)
{
  return (1.0 / gl_bunny_frequency);
}

