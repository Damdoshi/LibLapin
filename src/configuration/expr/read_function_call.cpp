// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

bool			expr_read_function_call(const char	*code,
						ssize_t		&i,
						Expression	&expr)
{
  char			buffer[256];
  Expression		*son;
  ssize_t		j, k;
  int			calltype;
  int			prev;

  expr_read_separator(code, i);
  if (code[i] == ')')
    return (true);
  calltype = 0;
  prev = 0;
  do
    {
      expr_read_separator(code, i);
      j = i;
      buffer[0] = '\0';
      if (readfield(code, j))
	{
	  k = j;
	  expr_read_separator(code, j);
	  if (readtext(code, j, "="))
	    {
	      if (k - i < (int)(sizeof(buffer) - 1))
		{
		  memcpy(&buffer[0], &code[i], k - i);
		  buffer[k - i] = '\0';
		}
	      else
		{
		  memcpy(&buffer[0], &code[i], sizeof(buffer) - 1);
		  buffer[sizeof(buffer) - 1] = '\0';
		}
	      expr_read_separator(code, j);
	      i = j;
	      calltype = -1;
	    }
	  else
	    calltype = 1;
	}
      else
	calltype = 1;

      if (code[i] != ',')
	{
	  if ((son = expr_read_operator
	       (code, i, Expression::BEOF_ASSIGNATION)) == NULL)
	    return (false);
	  son->val.name = &buffer[0];
	  son->line = expr.line;
	  expr_read_separator(code, i);
	  if (prev == 0)
	    prev = calltype;
	  else if (prev != calltype)
	    scream_error_if
	      (return (false), BE_SYNTAX_ERROR,
	       "Mixing named parameters with order "
	       "parameters is impossible on line %d",
	       "ressource,configuration,syntax",
	       whichline(code, i));
	}
      else
	son = NULL;
      expr.operand.push_back(son);
    }
  while (readtext(code, i, ","));
  return (true);
}

