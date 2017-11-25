// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			expr_precompute(Expression		&exp)
{
  return (expr_compute(exp, true, NULL, NULL, NULL, NULL));
}

