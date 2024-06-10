// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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
    &expr_compute_group,
    &expr_compute_low_bin,
    &expr_compute_high_bin,
    &expr_compute_shift,
    &expr_compute_low_math,
    &expr_compute_high_math,
    &expr_compute_pow,
    &expr_compute_cat,
  };

bool			expr_compute(SmallConf			&exp,
				     bool			dry,
				     SmallConf			*root,
				     // Local est défini ici car exp n'est pas
				     // forcement dans un champ.
				     // Il peut etre dans une fonction.
				     SmallConf			*local,
				     SmallConf			*artif,
				     SmallConf			*variables)
{
  if(exp.expression == NULL)
    {
      if (exp.have_value)
	return (true);
      return (false);
    }
  if (exp.expression->is_const)
    return (true);
  // C'est vraiment au cas ou
  if (!root)
    root = (SmallConf*)bunny_configuration_get_root((SmallConf*)&exp);
  if (!artif)
    artif = (SmallConf*)bunny_configuration_get_parent((SmallConf*)&exp);
  if (!local)
    local = &exp;
  int			cmode = SmallConf::create_mode;

  cmode = true;
  variables = test_and_set_prototype(exp, variables);
  if (exp.expression->optor_family == Expression::LAST_OPERATOR_FAMILY || exp.expression->optor_family == -1)
    {
      SmallConf		*ope;

      if (exp.expression->optor_family == -1)
	{
	  if ((ope = expr_get_variable
	       (exp.expression->val, dry, root, local, artif, variables)) ==
	      NULL)
	    scream_error_if
	      (goto ResetAndFalse, BE_BAD_ADDRESS,
	       "Undefined variable or unresolvable address %s from context %s on line %s:%d",
	       "ressource,configuration,syntax",
	       exp.expression->val.original_value.c_str(),
	       artif->address.c_str(),
	       exp.expression->file.c_str(), exp.line);
	  SmallConf::RecursiveAssign(exp, *ope);
	  goto ResetAndTrue;
	}
      if (expr_compute_function_call
	  (*exp.expression, dry, root, local, artif, variables) == false)
	goto ResetAndFalse;
      SmallConf::RecursiveAssign(exp, exp.expression->val);
      goto ResetAndTrue; // Y a des trucs a faire ici, encore, peut etre?
    }
  if (gl_expr_computation[exp.expression->optor_family]
      (*exp.expression, dry, root, local, artif, variables) == false)
    goto ResetAndFalse;

  // exp = exp.expression->val;
  SmallConf::RecursiveAssign(exp, exp.expression->val);

 ResetAndTrue:
  SmallConf::create_mode = cmode;
  return (true);
 ResetAndFalse:
  SmallConf::create_mode = cmode;
  return (false);
}

