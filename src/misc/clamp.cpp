// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin.h"


/**
 * @doc
 * @doc-symbol bunny_clamp
 * @doc-kind function
 * @doc-module misc
 * @doc-order 412
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Restricts a value to an inclusive interval.
 * @param value Value to restrict.
 * @param min Lower bound.
 * @param max Upper bound.
 * @return-success Returns min, max or value depending on the interval.
 * @see bunny_rclamp, bunny_reach
 *
 * @doc-lang fr
 * @brief Contraint une valeur dans un intervalle inclusif.
 * @param value Valeur à contraindre.
 * @param min Borne inférieure.
 * @param max Borne supérieure.
 * @return-success Renvoie min, max ou value selon l'intervalle.
 * @see bunny_rclamp, bunny_reach
 */
double			bunny_clamp(double		val,
				    double		min,
				    double		max)
{
  if (val < min)
    return (min);
  if (val > max)
    return (max);
  return (val);
}
