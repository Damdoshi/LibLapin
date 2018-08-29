// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Expression		*expr_read_operand(const char		*code,
					   ssize_t		&i)
{
  Expression		*last;

  if (readtext(code, i, "("))
    {
      expr_read_separator(code, i);
      if ((last = expr_read_operator(code, i, (size_t)Expression::BEO_ASSIGN)) == NULL)
	return (NULL);
      expr_read_separator(code, i);
      if (readtext(code, i, ")") == false)
	scream_error_if
	  (return (NULL), BE_SYNTAX_ERROR,
	   "Missing token ')' on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i));
      expr_read_separator(code, i);
      return (last);
    }
  expr_read_separator(code, i);
  last = new Expression;
  last->optor_family = -1;
  last->line = whichline(code, i);
  last->file = SmallConf::file_read.top();
  if (readvalue(code, i, last->val, NULL) == false)
    {
      if (readaddress(code, i, last->val) == false)
	{
	  delete last;
	  scream_error_if
	    (return (NULL), BE_SYNTAX_ERROR,
	     "A value was expected on line %s:%d",
	     "ressource,configuration,syntax",
	     SmallConf::file_read.top().c_str(), whichline(code, i));
	}
      if (check_keywords(last->val.original_value) == false)
	scream_error_if
	  (return (NULL), BE_SYNTAX_ERROR,
	   "A valid value was expected, found keyword '%s' on line %s:%d",
	   "ressource,configuration,syntax",
	   last->val.original_value.c_str(),
	   SmallConf::file_read.top().c_str(), whichline(code, i));

      last->val.symbol = true;
      last->val.name = last->val.original_value;
      expr_read_separator(code, i);
      if (readtext(code, i, "("))
	{
	  last->optor_family = Expression::LAST_OPERATOR_FAMILY;
	  if (last->val.name != "integer"
	      && last->val.name != "int"
	      && last->val.name != "real"
	      && last->val.name != "string")
	    {
	      if (expr_read_function_call(code, i, *last) == false)
		{
		  delete last;
		  return (NULL);
		}
	    }
	  else
	    {
	      Expression	*to_convert;

	      if (last->val.name == "integer" || last->val.name == "int")
		last->type_cast = Expression::INT_CAST;
	      else if (last->val.name == "real")
		last->type_cast = Expression::REAL_CAST;
	      else if (last->val.name == "string")
		last->type_cast = Expression::STRING_CAST;
	      if ((to_convert = expr_read_operator(code, i, (size_t)Expression::BEO_ASSIGN)) == NULL)
		return (NULL);
	      last->operand.push_back(to_convert);
	    }
	  if (readtext(code, i, ")") == false)
	    {
	      delete last;
	      scream_error_if
		(return (NULL), BE_SYNTAX_ERROR,
		 "The token ')' was expected to close function call on line %s:%d",
		 "ressource,configuration,syntax",
		 SmallConf::file_read.top().c_str(), whichline(code, i));
	    }
	}
      expr_read_separator(code, i);
    }
  else
    last->is_const = true;
  expr_read_separator(code, i);
  return (last);
}

