// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<iostream>
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
				     SmallConf			*prototype,
				     bool			dry,
				     SmallConf			*root,
				     SmallConf			*local,
				     SmallConf			*artif,
				     SmallConf			*param)
{
  int			cmode;
  size_t		i;

  if(exp.expression == NULL)
    {
      if (exp.have_value)
	return (true);
      return (false);
    }
  if (exp.expression->is_const)
    return (true);
  if (prototype)
    {
      if (param == NULL)
	scream_error_if
	  (return (false), BE_SYNTAX_ERROR,
	   "Missing parameters for function or expression %s on line %s:%d",
	   "ressource,configuration,syntax",
	   exp.name.c_str(), exp.expression->file.c_str(), exp.line
	   );
      for (i = 0; i < prototype->Size(); ++i)
	{
	  if (param->Access((*prototype)[i].name) == false)
	    {
	      if ((*prototype)[i].have_value)
		{
		  cmode = SmallConf::create_mode;
		  SmallConf::create_mode = true;
		  (*param)[(*prototype)[i].name] = (*prototype)[i];
		  SmallConf::create_mode = cmode;
		}
	      else
		scream_error_if
		  (return (false), BE_SYNTAX_ERROR,
		   "Missing parameters n=%zu (%s) for function or expression %s on line %s:%d",
		   "ressource,configuration,syntax",
		   i, (*prototype)[i].name.c_str(), exp.name.c_str(), exp.expression->file.c_str(), exp.line
		   );
	    }
	}
    }
  if (exp.expression->optor_family == Expression::LAST_OPERATOR_FAMILY
      || exp.expression->optor_family == -1)
    {
      SmallConf		*ope;

      if (exp.expression->optor_family == -1)
	{
	  if ((ope = expr_get_variable
	       (exp.expression->val, dry, root, local, artif, param)) ==
	      NULL)
	    scream_error_if
	      (return (false), BE_BAD_ADDRESS,
	       "Undefined variable or unresolvable address %s from context %s on line %s:%d",
	       "ressource,configuration,syntax",
	       exp.expression->val.original_value.c_str(),
	       artif->address.c_str(),
	       exp.expression->file.c_str(), exp.line);
	  exp = *ope;
	  return (true);
	}
      if (expr_compute_function_call
	  (*exp.expression, dry, root, local, artif, param) == false)
	return (false);
      exp = exp.expression->val;
      return (true); // Y a des trucs a faire ici, encore, peut etre?
    }
  if (gl_expr_computation[exp.expression->optor_family]
      (*exp.expression, dry, root, local, artif, param) == false)
    return (false);
  exp = exp.expression->val;
  return (true);
}

