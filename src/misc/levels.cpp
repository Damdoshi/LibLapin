// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_next_level_experience
 * @doc-kind function
 * @doc-module misc
 * @doc-order 350
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Computes a simple triangular experience curve.
 * @param lvl Current level.
 * @return-success Returns the experience amount required to reach the next level step.
 *
 * @doc-lang fr
 * @brief Calcule une courbe d'expérience triangulaire simple.
 * @param lvl Niveau courant.
 * @return-success Renvoie la quantité d'expérience nécessaire pour atteindre le palier suivant.
 */
int			bunny_next_level_experience(int		lvl)
{
  lvl += 1;
  return (lvl * (lvl - 1) / 2);
}

