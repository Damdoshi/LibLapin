// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_reach
 * @doc-kind function
 * @doc-module misc
 * @doc-order 410
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Moves a scalar value toward a limit by a fixed step.
 * @param value Value to update.
 * @param limit Target value.
 * @param step Movement step.
 * @return-success Returns true when value reaches limit during this call.
 * @return-failure Returns false while value is still moving.
 * @see bunny_clamp, bunny_rclamp
 *
 * @doc-lang fr
 * @brief Déplace une valeur scalaire vers une limite avec un pas fixe.
 * @param value Valeur à mettre à jour.
 * @param limit Valeur cible.
 * @param step Pas du déplacement.
 * @return-success Renvoie true lorsque value atteint limit pendant cet appel.
 * @return-failure Renvoie false tant que value est encore en mouvement.
 * @see bunny_clamp, bunny_rclamp
 */
bool			bunny_reach(double		*value,
				    double		limit,
				    double		step)
{
  if (fabs(*value - limit) < step)
    {
      *value = limit;
      return (true);
    }

  if (*value < limit)
    {
      if ((*value += step) > limit)
	{
	  *value = limit;
	  return (true);
	}
      return (false);
    }

  if (*value > limit)
    {
      if ((*value -= step) < limit)
	{
	  *value = limit;
	  return (true);
	}
      return (false);
    }

  return (false);
}

