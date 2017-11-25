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
      if ((last = expr_read_operator(code, i, (size_t)Expression::BEO_ASSIGN)) == NULL)
	return (NULL);
      if (readtext(code, i, ")") == false)
	scream_error_if
	  (return (NULL), BE_SYNTAX_ERROR,
	   "Missing token ')' on line %d",
	   whichline(code, i));
      return (last);
    }
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
	     whichline(code, i));
	}
    }
  else
    last->is_const = true;
  return (last);
}

