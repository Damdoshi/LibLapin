// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			expr_compute_group(Expression		&exp,
					   bool			dry,
					   SmallConf		*root,
					   SmallConf		*local,
					   SmallConf		*artif,
					   SmallConf		*param)
{
  bool			cnst;
  int			tmp;
  bool			res;
  size_t		i;

  SmallConf		*first;

  first = NULL;
  if (exp.is_const)
    return (true);

  res = false;
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
      if (first == NULL)
	first = ope;
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

      ope->GetInt(&tmp);
      if (i == 0)
	{}
      else if (i != 1)
	scream_error_if
	  (return (false), BE_SYNTAX_ERROR,
	   "Operator 'in' and 'out' cannot be chained on line %s:%d",
	   "ressource,configuration,syntax",
	   exp.file.c_str(), exp.line);
      else
	{
	  bool		in =
	    x.optor >= Expression::BEO_IN && x.optor <= Expression::BEO_INSCOPE;
	  int		type;

	  if (in)
	    type = x.optor - Expression::BEO_IN;
	  else
	    type = x.optor - Expression::BEO_OUT;
	  SmallConf	&tab = *ope;
	  std::vector<SmallConf*>::iterator it;
	  std::map<std::string, SmallConf*>::iterator itn;

	  // Récupérer la position plutot qu'une simple
	  // presence serait interessant, mais il faudrait que "in" renvoi
	  // -1 en cas d'absence afin d'éviter une ambiguié (j'ai pas envie
	  // d'un === comme en PHP
	  // mais "in" n'a pas ce sens, et si "in" avait ce sens, alors
	  // "out" ne serait pas que la simple inversion de "in"...
	  
	  res = false;
	  if (type == 0 || type == 1)
	    {
	      for (it = tab.array.begin(); it != tab.array.end(); ++it)
		if (*first == **it)
		  {
		    res = true;
		    break ;
		  }
	    }
	  if (type == 0 || type == 2)
	    {
	      for (itn = tab.nodes.begin(); itn != tab.nodes.end(); ++itn)
		if (first->original_value == itn->first)
		  {
		    res = true;
		    break ;
		  }
	    }
	  if (in)
	    res = res;
	  else
	    res = !res;
	}
    }
  if (dry && cnst == false)
    return (true);
  exp.val.SetInt(res);
  if (cnst)
    exp.is_const = true;
  return (true);
}

