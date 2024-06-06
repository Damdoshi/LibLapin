// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			expr_precompute(SmallConf		&exp)
{
  return (true); // Sabotage du précalcul car ca génère trop de merde.
  return (expr_compute(exp, true, NULL, NULL, NULL, NULL));
}

