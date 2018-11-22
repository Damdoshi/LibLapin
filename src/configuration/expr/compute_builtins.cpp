// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_decision	expr_compute_builtins(Expression	&exp,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*param)
{
  std::string		bin;

  if (exp.val.name != "")
    bin = exp.val.name;
  else
    bin = exp.val.original_value;

  // SINGLE OPERAND KEYWORDS

  if (exp.operand.size() != 1)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "Keyword NbrChildren only takes one parameter on line %s:%d",
       "ressource,configuration,syntax",
       exp.file.c_str(), exp.line);

  if (bunny_strcasecmp(bin.c_str(), "AddressOf") == 0)
    {
      if (exp.operand.size() != 1)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "Keyword AddressOf only takes one parameter on line %s:%d",
	   "ressource,configuration,syntax",
	   exp.file.c_str(), exp.line);
      exp.val.SetString(exp.operand[0]->val.address, true);
      return (BD_OK);
    }

  // VARIABLE OPERAND KEYWORDS

  SmallConf		*ope;

  if ((ope = expr_get_variable(exp.operand[0]->val, dry, root, local, artif, param)) == NULL)
    scream_error_if
      (return (BD_ERROR), BE_BAD_ADDRESS,
       "Undefined node %s from context %s on line %s:%d",
       "configuration,syntax",
       exp.val.original_value.c_str(),
       artif->address.c_str(),
       exp.file.c_str(), exp.line);

  if (bunny_strcasecmp(bin.c_str(), "HaveValue") == 0)
    {
      exp.val.SetInt((int)ope->have_value);
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "NbrChildren") == 0)
    {
      exp.val.SetInt(ope->NbrChild());
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "NbrCase") == 0)
    {
      exp.val.SetInt(ope->Size());
      return (BD_OK);
    }
  if (bunny_strcasecmp(bin.c_str(), "IsEmpty") == 0)
    {
      exp.val.SetInt(ope->Size() == 0 && ope->NbrChild() && ope->have_value == false);
      return (BD_OK);
    }

  return (BD_NOT_FOUND);
}

