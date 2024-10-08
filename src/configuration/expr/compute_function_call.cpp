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
//   .prototype = [Array
//      "parameter name"
//   ]
//   .cNUMBER = [Node ???????????????????????
//      variables
//   ]
// ]

// Variables smallconf:
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
						   SmallConf	*variables)
{
  SmallConf		*ope;
  t_bunny_decision	ret;
  size_t		i;

  if (exp.type_cast != Expression::NO_CAST)
    return (expr_compute_cast(exp, dry, root, local, artif, variables));
  if ((ret = expr_compute_builtins(exp, dry, root, local, artif, variables)) == BD_ERROR)
    return (false);
  if (ret == BD_OK)
    return (true);
  exp.is_const = false;

  // On récupère la fonction ciblée
  if ((ope = expr_get_variable(exp.val, dry, root, local, artif, variables)) == NULL)
    scream_error_if
      (return (false), BE_BAD_ADDRESS,
       "Undefined function %s from context %s on line %s:%d",
       "configuration,syntax",
       exp.val.original_value.c_str(),
       artif ? artif->address.c_str() : local->address.c_str(),
       exp.file.c_str(), exp.line);
  if (ope == &exp.val)
    return (true);

  SmallConf		temp_param;
  SmallConf		*parameters = NULL;
  SmallConf		*proto = NULL;
  bool			cmode = SmallConf::create_mode;

  // On récupère le prototype de la fonction ciblée
  SmallConf::create_mode = true;
  proto = &(*ope)[".prototype"];

  // Y a t il des paramètres ?
  if (exp.operand.size())
    {
      // Les paramètres sont ils passé par ordre?
      if (exp.operand[0]->val.name == "")
	{
	  for (i = 0; i < exp.operand.size() && i < (*proto).Size(); ++i)
	    if (exp.operand[i] != NULL)
	      {
		Expression	&arg = *exp.operand[i];
		SmallConf	*oparg, *tmp;

		if (arg.operand.size() > 1)
		  if (gl_expr_computation[arg.optor_family]
		      (arg, dry, root, local, artif, variables) == false)
		    {
		      SmallConf::create_mode = cmode;
		      return (false);
		    }
		oparg = &arg.val;
		// Le résultat peut etre une adresse ou un nom de variable.
		// Par exemple func(v)... v est le resultat.
		// Donc il faut pouvoir résoudre le nom de variable final.
		if (oparg->last_type == SmallConf::RAWSTRING)
		  {
		    if ((tmp = expr_get_variable
			 (*oparg, dry, root, local, artif, variables)) == NULL)
		      if (!bunny_configuration_is_type(root, arg.val.original_value.c_str()))
			scream_error_if
			  (return (false), BE_BAD_ADDRESS,
			   "Undefined variable or unresolvable address %s "
			   "from context %s on line %s:%d",
			   "ressource,configuration,syntax",
			   arg.val.original_value.c_str(),
			   artif->address.c_str(),
			   exp.file.c_str(), exp.line);
		    if (tmp)
		      oparg = tmp;
		  }
		SmallConf::RecursiveAssign(temp_param[(*proto)[i].name], *oparg);
	      }
	}
      // Ils sont envoyé par nom
      else
	for (i = 0; i < exp.operand.size(); ++i)
	  if (exp.operand[i] != NULL)
	    {
	      Expression	&arg = *exp.operand[i];
	  
	      if (arg.optor_family != -1 && gl_expr_computation[arg.optor_family]
		  (arg, dry, root, local, artif, variables) == false)
		{
		  SmallConf::create_mode = cmode;
		  return (false);
		}
	      SmallConf::RecursiveAssign(temp_param[arg.val.name], arg.val);
	    }
    }
  parameters = &temp_param;
  SmallConf::create_mode = cmode;

  SmallConf		*tmp_artif = ope->father ? ope->father : ope;

  if (ope->expression)
    {
      if (expr_compute // Local a tmp_artif car on repart sur une autre fonction
	  (*ope, dry, root, tmp_artif, tmp_artif, parameters) == false)
	return (false);
    }
  else if (ope->function)
    {
      if (dabsic_compute
	  (*ope, dry, root, tmp_artif, parameters) == false)
	return (false);
    }
  else if (ope->sequence)
    {
      if (sequence_compute
	  // Le NULL sera a retiré quand sequence_compute pourra être modifié
	  (*ope, NULL, root, tmp_artif, parameters, NULL, NULL) == false)
	return (false);
    }
  else if (dry)
    return (true);
  else
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       "Node %s is not a function on line %s:%d",
       "configuration,syntax",
       exp.val.original_value.c_str(), exp.file.c_str(), exp.line);
  auto save = ope->expression;

  // Hack nul parceque exp.val = *ope va appeller expr_compute mais sans les paramètres
  // si ope->expression existe. Il faudrait probablement que expr_compute
  // puisse stocker quelque part le resultat directement pour eviter ca.
  ope->expression = NULL;
  SmallConf::RecursiveAssign(exp.val, *ope);
  ope->expression = save;
  return (true);
}

