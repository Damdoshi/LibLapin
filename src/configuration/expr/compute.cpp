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

bool			expr_compute(SmallConf			&exp,
				     bool			dry,
				     SmallConf			*root,
				     SmallConf			*local,
				     SmallConf			*artif,
				     SmallConf			*param)
{
  if (exp.expression->is_const)
    return (true);
  if (exp.expression->optor_family == Expression::LAST_OPERATOR_FAMILY
      || exp.expression->optor_family == -1)
    {
      SmallConf		*ope;

      if ((ope = expr_get_variable
	   (exp.expression->val, dry, root, local, artif, param)) ==
	  NULL)
	scream_error_if
	  (return (false), BE_BAD_ADDRESS,
	   "Undefined variable or unresolvable address %s on line %d",
	   "ressource,configuration,syntax",
	   exp.expression->val.original_value.c_str(), exp.line);
      exp = *ope;

      return (true); // Y a des trucs a faire ici.
    }
  if (gl_expr_computation[exp.expression->optor_family]
      (*exp.expression, dry, root, local, artif, param) == false)
    return (false);
  exp = exp.expression->val;
  return (true);
}


