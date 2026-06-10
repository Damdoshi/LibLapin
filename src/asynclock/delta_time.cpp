// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<time.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_delta_time
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Computes the difference between two timestamps.
 * @description bunny_delta_time subtracts before from after and returns the elapsed time in nanoseconds. Both timestamps should come from the same clock source, typically bunny_get_time.
 * @param before The oldest timestamp.
 * @param after The youngest timestamp.
 * @return-case success On $Bsuccess@, returns after minus before, in nanoseconds.
 * @see bunny_get_time
 *
 * @doc-lang fr
 * @brief Calcule la différence entre deux timestamps.
 * @description bunny_delta_time soustrait before à after et renvoie le temps écoulé en nanosecondes. Les deux timestamps devraient venir de la même source d'horloge, typiquement bunny_get_time.
 * @param before Le timestamp le plus ancien.
 * @param after Le timestamp le plus récent.
 * @return-case success En cas de $Bsuccès@, renvoie after moins before, en nanosecondes.
 * @see bunny_get_time
 */
t_bunny_time		bunny_delta_time(t_bunny_time		before,
				 t_bunny_time		after)
{
  return (after - before);
}
