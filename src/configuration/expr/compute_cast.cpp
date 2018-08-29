// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<iostream>
#include		"lapin_private.h"

bool			expr_compute_cast(Expression		&exp,
					  bool			dry,
					  SmallConf		*root,
					  SmallConf		*local,
					  SmallConf		*artif,
					  SmallConf		*param)
{
  SmallConf		&x = exp.operand[0]->val;
  const char		*str;
  int			i;
  double		d;

  if (exp.operand[0]->operand.size() > 1)
    {
      if (gl_expr_computation[exp.operand[0]->optor_family]
	  (*exp.operand[0], dry, root, local, artif, param) == false)
	return (false);
    }
  SmallConf		*ope;

  ope = &x;
  if (ope->last_type == SmallConf::RAWSTRING)
    {
      if ((ope = expr_get_variable
	   (*ope, dry, root, local, artif, param)) == NULL)
	scream_error_if
	  (return (false), BE_BAD_ADDRESS,
	   "Undefined variable or unresolvable address %s "
	   "from context %s on line %s:%d",
	   "configuration,syntax",
	   x.original_value.c_str(),
	   artif->address.c_str(),
	   exp.file.c_str(), exp.line);
    }

  if (exp.type_cast == Expression::INT_CAST)
    {
      if (ope->last_type == SmallConf::STRING)
	{
	  ope->GetString(&str, NULL, NULL, NULL, NULL);
	  if (strcmp(str, "true") == 0)
	    exp.val.SetInt(1);
	  else
	    exp.val.SetInt(strtol(str, NULL, 0));
	}
      else if (ope->last_type == SmallConf::DOUBLE)
	{
	  ope->GetDouble(&d, NULL, NULL, NULL, NULL);
	  exp.val.SetInt(d);
	}
      else
	exp.val = *ope;
    }
  else if (exp.type_cast == Expression::REAL_CAST)
    {
      if (ope->last_type == SmallConf::STRING)
	{
	  ope->GetString(&str, NULL, NULL, NULL, NULL);
	  if (strcmp(str, "true") == 0)
	    exp.val.SetDouble(1);
	  else
	    exp.val.SetDouble(strtod(str, NULL));
	}
      else if (ope->last_type == SmallConf::INTEGER)
	{
	  ope->GetInt(&i, NULL, NULL, NULL, NULL);
	  exp.val.SetInt(i);
	}
      else
	exp.val = *ope;
    }
  else if (exp.type_cast == Expression::STRING_CAST)
    {
      if (ope->last_type == SmallConf::DOUBLE)
	{
	  std::stringstream	ss;

	  ope->GetDouble(&d, NULL, NULL, NULL, NULL);
	  ss << d;
	  exp.val.SetString(ss.str());
	}
      else if (ope->last_type == SmallConf::INTEGER)
	{
	  std::stringstream	ss;

	  ope->GetInt(&i, NULL, NULL, NULL, NULL);
	  ss << i;
	  exp.val.SetString(ss.str());
	}
      else
	exp.val = *ope;
    }
  return (true);
}
