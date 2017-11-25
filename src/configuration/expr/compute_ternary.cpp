// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			expr_compute_ternary(Expression		&exp,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*param)
{
  if (exp.operand.size() != 3)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "Incomplete ternary on line %d",
       exp.line);
  if (exp.operand[1]->optor != Expression::BEO_TERNARY)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "First ternary token must be '?' on line %d",
       exp.line);
  if (exp.operand[2]->optor != Expression::BEO_TERNARY_ELSE)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "Second ternary token must be ':' on line %d",
       exp.line);
  Expression		*x = exp.operand[0];
  int			tmp;

  if (x->optor_family == -1)
    {} // Operand
  else if (gl_expr_computation[x->optor_family]
	   (*x, dry, root, local, artif, param) == false)
    return (false);
  SmallConf		*ope;

  if (x->val.GetInt(&tmp) == false)
    scream_error_if
      (return (false), BE_TYPE_ERROR,
       "Cannot evaluate the truthness of the main ternary operand on line %d",
       exp.line);

  if (tmp)
    x = exp.operand[1];
  else
    x = exp.operand[2];

  if (x->optor_family == -1)
    {} // Operand
  else if (gl_expr_computation[x->optor_family]
	   (*x, dry, root, local, artif, param) == false)
    return (false);

  exp.val = x->val;
  return (true);
}

