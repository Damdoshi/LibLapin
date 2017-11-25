// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

const t_expr_computation gl_expr_computation[Expression::LAST_OPERATOR_FAMILY] =
  {
    &expr_compute_assign,
    &expr_compute_ternary,
    &expr_compute_low_logic,
    &expr_compute_high_logic,
    &expr_compute_test,
    &expr_compute_low_bin,
    &expr_compute_high_bin,
    &expr_compute_shift,
    &expr_compute_low_math,
    &expr_compute_high_math,
    &expr_compute_pow,
    &expr_compute_cat
  };

bool			expr_compute(Expression			&exp,
				     bool			dry,
				     SmallConf			*root,
				     SmallConf			*local,
				     SmallConf			*artif,
				     SmallConf			*param)
{
  if (exp.is_const)
    return (true);
  if (exp.optor_family == Expression::LAST_OPERATOR_FAMILY
      || exp.optor_family == -1)
    return (true); // Y a des trucs a faire ici.
  return (gl_expr_computation[exp.optor_family](exp, dry, root, local, artif, param));
}


