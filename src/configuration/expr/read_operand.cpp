// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
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
	   "Missing token ')' on line %d",
	   "ressource,configuration,syntax",
	   whichline(code, i));
      expr_read_separator(code, i);
      return (last);
    }
  expr_read_separator(code, i);
  last = new Expression;
  last->line = whichline(code, i);
  if (readvalue(code, i, last->val, NULL) == false)
    {
      if (readaddress(code, i, last->val) == false)
	{
	  delete last;
	  scream_error_if
	    (return (NULL), BE_SYNTAX_ERROR,
	     "A value was expected on line %d",
	     "ressource,configuration,syntax",
	     whichline(code, i));
	}
      if (check_keywords(last->val.original_value) == false)
	scream_error_if
	  (return (NULL), BE_SYNTAX_ERROR,
	   "A value was expected on line %d",
	   "ressource,configuration,syntax",
	   whichline(code, i));
    }
  else
    last->is_const = true;
  expr_read_separator(code, i);
  return (last);
}

