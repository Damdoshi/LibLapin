// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin.h"


/**
 * @doc
 * @doc-symbol bunny_rclamp
 * @doc-kind function
 * @doc-module misc
 * @doc-order 414
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Wraps a value around an interval.
 * @param value Value to wrap.
 * @param min Lower bound.
 * @param max Upper bound.
 * @return-success Returns max when value is below min, min when value is above max, otherwise value.
 * @see bunny_clamp, bunny_reach
 *
 * @doc-lang fr
 * @brief Reboucle une valeur autour d'un intervalle.
 * @param value Valeur à reboucler.
 * @param min Borne inférieure.
 * @param max Borne supérieure.
 * @return-success Renvoie max si value est sous min, min si value est au-dessus de max, sinon value.
 * @see bunny_clamp, bunny_reach
 */
double			bunny_rclamp(double		val,
				     double		min,
				     double		max)
{
  if (val < min)
    return (max);
  if (val > max)
    return (min);
  return (val);
}
