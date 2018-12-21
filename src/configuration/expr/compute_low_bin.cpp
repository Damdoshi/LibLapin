// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			expr_compute_low_bin(Expression	&exp,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*param)
{
  bool			cnst;
  int			tmp;
  int			sum;
  size_t		i;

  if (exp.is_const)
    return (true);

  sum = 0;
  cnst = true;
  for (i = 0; i < exp.operand.size(); ++i)
    {
      Expression	&x = *exp.operand[i];
      SmallConf		*ope;

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
	       "ressource,configuration,syntax",
	       exp.operand[i]->val.original_value.c_str(),
	       artif->address.c_str(),
	       exp.file.c_str(), exp.line);
	}
      else if (x.is_const == false)
	cnst = false;

      if (expr_test_type(*ope, SmallConf::INTEGER) == false)
	scream_error_if
	  (return (false), BE_TYPE_ERROR,
	   "Operator '|' and '^' can only be used on integer on line %s:%d",
	   "ressource,configuration,syntax",
	   exp.file.c_str(), exp.line);

      ope->GetInt(&tmp);
      if (i == 0)
	sum = tmp;
      else if (x.optor == Expression::BEO_BIN_OR)
	sum |= tmp;
      else if (x.optor == Expression::BEO_BIN_XOR)
	sum ^= tmp;
    }
  if (dry && cnst == false)
    return (true);
  exp.val.SetInt(sum);
  if (cnst)
    exp.is_const = true;
  return (true);
}

