// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			expr_compute_test(Expression		&exp,
					  bool			dry,
					  SmallConf		*root,
					  SmallConf		*local,
					  SmallConf		*artif,
					  SmallConf		*param)
{
  bool			cnst;
  size_t		i;
  bool			res;

  if (exp.is_const)
    return (true);

  if (exp.operand.size() > 0 && exp.operand[0]->optor_family != -1)
    {
      cnst = exp.operand[0]->is_const;
      if (gl_expr_computation[exp.operand[0]->optor_family]
	  (*exp.operand[0], dry, root, local, artif, param) == false)
	return (false);
    }
  else if (exp.operand[0]->val.symbol)
    cnst = exp.operand[0]->is_const;
  else
    cnst = true;

  res = true;
  for (i = 0; i < exp.operand.size() - 1; ++i)
    {
      Expression	&x = *exp.operand[i + 1];
      SmallConf		*left = &exp.operand[i]->val;
      SmallConf		*right = &x.val;
      int		optor = exp.operand[i + 1]->optor;

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

      if (left->last_type == SmallConf::RAWSTRING)
	{
	  cnst = false;
	  if ((left = expr_get_variable
	       (*left, dry, root, local, artif, param)) == NULL)
	    scream_error_if
	      (return (false), BE_BAD_ADDRESS,
	       "Undefined variable or unresolvable address %s "
	       "from context %s on line %s:%d",
	       "ressource,configuration,syntax",
	       left->original_value.c_str(),
	       artif->address.c_str(),
	       exp.file.c_str(), exp.line);
	}
      else if (exp.operand[i]->is_const == false)
	cnst = false;

      if (right->last_type == SmallConf::RAWSTRING)
	{
	  cnst = false;
	  if ((right = expr_get_variable
	       (*right, dry, root, local, artif, param)) == NULL)
	    scream_error_if
	      (return (false), BE_BAD_ADDRESS,
	       "Undefined variable or unresolvable address %s "
	       "from context %s on line %s:%d",
	       "ressource,configuration,syntax",
	       right->original_value.c_str(),
	       artif->address.c_str(),
	       exp.file.c_str(), exp.line);
	}
      else if (exp.operand[i + 1]->is_const == false)
	cnst = false;

      if (optor == Expression::BEO_EQUAL)
	{
	  if (!(*left == *right))
	    {
	      res = false;
	      break ;
	    }
	}
      else if (optor == Expression::BEO_REC_EQUAL)
	{
	  if (SmallConf::RecursiveCheck(*left, *right) == false)
	    {
	      res = false;
	      break ;
	    }
	}
      else if (optor == Expression::BEO_DIFF)
	{
	  if (*left == *right)
	    {
	      res = false;
	      break ;
	    }
	}
      else if (optor == Expression::BEO_REC_DIFF)
	{
	  if (SmallConf::RecursiveCheck(*left, *right))
	    {
	      res = false;
	      break ;
	    }
	}
      else if (optor == Expression::BEO_INF_EQU)
	{
	  if (*left > *right)
	    {
	      res = false;
	      break ;
	    }
	}
      else if (optor == Expression::BEO_GRT_EQU)
	{
	  if (*left < *right)
	    {
	      res = false;
	      break ;
	    }
	}
      else if (optor == Expression::BEO_INF)
	{
	  if (*left >= *right)
	    {
	      res = false;
	      break ;
	    }
	}
      else if (optor == Expression::BEO_GRT)
	{
	  if (*left <= *right)
	    {
	      res = false;
	      break ;
	    }
	}
    }
  if (dry && cnst == false)
    return (true);
  exp.val.SetInt(res);
  if (cnst)
    exp.is_const = true;
  return (true);
}


