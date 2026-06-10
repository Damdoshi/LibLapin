// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

sf::Clock		gl_bunny_current_time;

/**
 * @doc
 * @doc-symbol bunny_get_current_time
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 280
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Returns the current bunny-clock time.
 * @description bunny_get_current_time returns the LibLapin clock used by the loop and asynclock helpers. The returned value is expressed in seconds and is measured since the last bunny_reset_clock call, or since program initialization if the clock was never reset.
 * @return-case success On $Bsuccess@, returns the current bunny-clock time, in seconds.
 * @see bunny_reset_clock, bunny_asynclock
 *
 * @doc-lang fr
 * @brief Renvoie le temps courant de l'horloge bunny.
 * @description bunny_get_current_time renvoie l'horloge LibLapin utilisée par la boucle et les assistants asynclock. La valeur renvoyée est exprimée en secondes et mesurée depuis le dernier appel à bunny_reset_clock, ou depuis l'initialisation du programme si l'horloge n'a jamais été réinitialisée.
 * @return-case success En cas de $Bsuccès@, renvoie le temps courant de l'horloge bunny, en secondes.
 * @see bunny_reset_clock, bunny_asynclock
 */
double			bunny_get_current_time(void)
{
  return (gl_bunny_current_time.getElapsedTime().asMicroseconds() / 1e6);
}
