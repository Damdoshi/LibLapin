// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			expr_precompute(SmallConf		&exp)
{
  return (expr_compute(exp, NULL, true, NULL, NULL, NULL, NULL));
}

