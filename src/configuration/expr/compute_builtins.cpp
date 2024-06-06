// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static SmallConf	* _ecb(Expression			&exp,
			       bool				dry,
			       SmallConf			*root,
			       SmallConf			*local,
			       SmallConf			*artif,
			       SmallConf			*variables,
			       const std::string		&bin)
{
  SmallConf		*ope;

  if ((ope = expr_get_variable(exp.operand[0]->val, dry, root, local, artif, variables)) == NULL)
    {
      if (bunny_strcasecmp(bin.c_str(), "Exists") != 0)
	scream_error_if
	  (return (NULL), BE_BAD_ADDRESS,
	   "Undefined node %s from context %s on line %s:%d",
	   "configuration,syntax",
	   exp.val.original_value.c_str(),
	   artif->address.c_str(),
	   exp.file.c_str(), exp.line);
      exp.val.SetInt(0);
      return (ope);
    }
  return (ope);
}

t_bunny_decision	expr_compute_builtins(Expression	&exp,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*variables)
{
  std::string		bin;
  SmallConf		*ope;

  if (exp.val.name != "")
    bin = exp.val.name;
  else
    bin = exp.val.original_value;
  
  if (bunny_strcasecmp(bin.c_str(), "Exists") == 0)
    {
      if (exp.operand.size() != 1)
	goto BadAmountOfVariableseters;
      if ((ope = _ecb(exp, dry, root, local, artif, variables, bin)) == NULL)
	exp.val.SetInt(0);
      else
	exp.val.SetInt(1);
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "AddressOf") == 0)
    {
      if (exp.operand.size() != 1)
	goto BadAmountOfVariableseters;
      if ((ope = _ecb(exp, dry, root, local, artif, variables, bin)) == NULL)
	return (BD_ERROR);
      std::string croot = "[].";

      croot += ope->address;
      exp.val.SetString(croot, true);
      // exp.val.SetString(ope->address, false);
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "NameOf") == 0)
    {
      if (exp.operand.size() != 1)
	goto BadAmountOfVariableseters;
      if ((ope = _ecb(exp, dry, root, local, artif, variables, bin)) == NULL)
	return (BD_ERROR);
      exp.val.SetString(ope->name, false);
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "HaveValue") == 0)
    {
      if (exp.operand.size() != 1)
	goto BadAmountOfVariableseters;
      if ((ope = _ecb(exp, dry, root, local, artif, variables, bin)) == NULL)
	return (BD_ERROR);
      exp.val.SetInt((int)ope->have_value);
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "NbrChildren") == 0)
    {
      if (exp.operand.size() != 1)
	goto BadAmountOfVariableseters;
      if ((ope = _ecb(exp, dry, root, local, artif, variables, bin)) == NULL)
	return (BD_ERROR);
      exp.val.SetInt(ope->NbrChild());
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "NbrCases") == 0)
    {
      if (exp.operand.size() != 1)
	goto BadAmountOfVariableseters;
      if ((ope = _ecb(exp, dry, root, local, artif, variables, bin)) == NULL)
	return (BD_ERROR);
      exp.val.SetInt(ope->Size());
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "IsEmpty") == 0)
    {
      if (exp.operand.size() != 1)
	goto BadAmountOfVariableseters;
      if ((ope = _ecb(exp, dry, root, local, artif, variables, bin)) == NULL)
	return (BD_ERROR);
      exp.val.SetInt(ope->Size() == 0 && ope->NbrChild() == 0 && ope->have_value == false);
      return (BD_OK);
    }

  return (BD_NOT_FOUND);
 BadAmountOfVariableseters:
  scream_error_if
    (return (BD_ERROR), BE_SYNTAX_ERROR,
     "Builtin function %s only takes one parameter on line %s:%d",
     "ressource,configuration,syntax",
     bin.c_str(), exp.file.c_str(), exp.line);
  return (BD_ERROR);
}

