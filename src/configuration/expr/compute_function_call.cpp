// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<iostream>
#include		"lapin_private.h"

// Function call is stored like this:
//
// [expression->val -> function name
//  expression->operand[] -> [
//     val name -> parameter name
//     val value -> variable value
//   ]
// ]

// Prototype:
//
// [function_node
//   .parameter = [Array
//      "parameter name"
//   ]
// ]

// Param smallconf:
// [
//   name = val
//   name = val
//   ...
// ]

bool			expr_compute_function_call(Expression	&exp,
						   bool		dry,
						   SmallConf	*root,
						   SmallConf	*local,
						   SmallConf	*artif,
						   SmallConf	*param)
{
  SmallConf		*ope;
  size_t		i;

  (void)param;
  if (exp.type_cast != Expression::NO_CAST)
    return (expr_compute_cast(exp, dry, root, local, artif, param));
  exp.is_const = false;
  if ((ope = expr_get_variable(exp.val, dry, root, local, artif, param)) == NULL)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "Undefined function %s from context %s on line %s:%d",
       "configuration,syntax",
       exp.val.original_value.c_str(),
       artif->address.c_str(),
       exp.file.c_str(), exp.line);
  if (ope == &exp.val)
    return (true);

  SmallConf		temp_param;
  SmallConf		*parameters = NULL;
  SmallConf		*proto = NULL;

  if (exp.operand.size())
    {
      bool		cmode = SmallConf::create_mode;

      proto = &(*ope)[".parameters"];
      SmallConf::create_mode = true;

      if (exp.operand[0]->val.name == "")
	{
	  for (i = 0; i < exp.operand.size() && i < (*proto).Size(); ++i)
	    if (exp.operand[i] != NULL)
	      {
		Expression	&arg = *exp.operand[i];
		SmallConf	*oparg;

		if (arg.operand.size() > 1)
		  if (gl_expr_computation[arg.optor_family]
		      (arg, dry, root, local, artif, param) == false)
		    {
		      SmallConf::create_mode = cmode;
		      return (false);
		    }
		oparg = &arg.val;
		if (oparg->last_type == SmallConf::RAWSTRING)
		  {
		    if ((oparg = expr_get_variable
			 (*oparg, dry, root, local, artif, param)) == NULL)
		      scream_error_if
			(return (false), BE_BAD_ADDRESS,
			 "Undefined variable or unresolvable address %s "
			 "from context %s on line %s:%d",
			 "ressource,configuration,syntax",
			 arg.val.original_value.c_str(),
			 artif->address.c_str(),
			 exp.file.c_str(), exp.line);
		  }
		temp_param[(*proto)[i].name] = *oparg;
	      }
	}
      else
	for (i = 0; i < exp.operand.size(); ++i)
	  if (exp.operand[i] != NULL)
	    {
	      Expression	&arg = *exp.operand[i];

	      if (arg.optor_family != -1 && gl_expr_computation[arg.optor_family]
		  (arg, dry, root, local, artif, param) == false)
		{
		  SmallConf::create_mode = cmode;
		  return (false);
		}
	      temp_param[arg.val.name] = arg.val;
	    }
      parameters = &temp_param;
      SmallConf::create_mode = cmode;
    }
  SmallConf		*tmp_artif = ope->father ? ope->father : ope;

  if (ope->expression)
    {
      if (expr_compute
	  (*ope, proto, dry, root, NULL, tmp_artif, parameters) == false)
	return (false);
      exp.val = *ope;
      return (true);
    }
  if (ope->function)
    {
      if (dabsic_compute
	  (*ope, proto, dry, root, tmp_artif, parameters) == false)
	return (false);
      exp.val = *ope;
      return (true);
    }
  if (dry)
    return (true);
  scream_error_if
    (return (false), BE_SYNTAX_ERROR,
     "Node %s is not a function on line %s:%d",
     "configuration,syntax",
     exp.val.original_value.c_str(), exp.file.c_str(), exp.line);
  return (false);
}

