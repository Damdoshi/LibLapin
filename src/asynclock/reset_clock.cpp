// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_reset_clock
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 260
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Resets the bunny clock.
 * @description bunny_reset_clock restarts the internal LibLapin clock used by bunny_get_current_time and the asynclock helpers.
 * @return-case success On $Bsuccess@, returns the new bunny-clock time, currently 0 seconds.
 * @log "asynclock"
 * @see bunny_get_current_time
 *
 * @doc-lang fr
 * @brief Réinitialise l'horloge bunny.
 * @description bunny_reset_clock redémarre l'horloge interne de la LibLapin utilisée par bunny_get_current_time et les assistants asynclock.
 * @return-case success En cas de $Bsuccès@, renvoie le nouveau temps de l'horloge bunny, actuellement 0 seconde.
 * @log "asynclock"
 * @see bunny_get_current_time
 */
double			bunny_reset_clock(void)
{
  gl_bunny_current_time.restart();
  scream_log_if("%s", "asynclock", "");
  return (0);
}
