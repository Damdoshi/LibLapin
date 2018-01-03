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
  if (exp.is_const)
    return (true);

  if (exp.operand.size() != 3)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "Incomplete ternary on line %s:%d",
       "configuration,syntax",
        exp.file.c_str(), exp.line);
  if (exp.operand[1]->optor != Expression::BEO_TERNARY)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "First ternary token must be '?' on line %s:%d",
       "configuration,syntax",
       exp.file.c_str(),exp.line);
  if (exp.operand[2]->optor != Expression::BEO_TERNARY_ELSE)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "Second ternary token must be ':' on line %s:%d",
       "configuration,syntax",
       exp.file.c_str(), exp.line);
  if (dry)
    return (true);
  Expression		&x = *exp.operand[0];
  Expression		*y;
  SmallConf		*ope;
  bool			cnst;
  int			tmp;

  cnst = true;
  if (x.optor_family == -1)
    {}
  else if (x.optor_family == Expression::LAST_OPERATOR_FAMILY)
    {
      if (expr_compute_function_call(x, dry, root, local, artif, param) == false)
	return (false);
    }
  else if (gl_expr_computation[x.optor_family]
	   (x, dry, root, local, artif, param) == false)
    return (false);

  ope = &x.val;
  if (ope->last_type == SmallConf::RAWSTRING)
    {
      cnst = false;
      if ((ope = expr_get_variable
	   (*ope, dry, root, local, artif, param)) == NULL)
	scream_error_if
	  (return (false), BE_BAD_ADDRESS,
	   "Undefined variable or unresolvable address %s "
	   "from context %s on line %s:%d",
	   "configuration,syntax",
	   x.val.original_value.c_str(),
	   artif->address.c_str(),
	   exp.file.c_str(), exp.line);
    }
  else if (x.is_const == false)
    cnst = false;

  if (ope->GetInt(&tmp) == false)
    scream_error_if
      (return (false), BE_TYPE_ERROR,
       "Cannot evaluate the truthness of the main ternary operand on line %s:%d",
       "configuration,syntax",
       exp.file.c_str(), exp.line);

  if (tmp)
    y = exp.operand[1];
  else
    y = exp.operand[2];

  if (y->optor_family == -1)
    {}
  else if (y->optor_family == Expression::LAST_OPERATOR_FAMILY)
    {
      if (expr_compute_function_call(*y, dry, root, local, artif, param) == false)
	return (false);
    }
  else if (gl_expr_computation[y->optor_family]
	   (*y, dry, root, local, artif, param) == false)
    return (false);

  exp.val = y->val;
  if (cnst)
    exp.is_const = true;
  return (true);
}

