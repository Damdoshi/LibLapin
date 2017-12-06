// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_statement(const char	*code,
					      ssize_t		&i,
					      Function		&func,
					      SmallConf		&funcnode,
					      SmallConf		&root)
{
  dabsic_read_separator(code, i);
  func.line = whichline(code, i);
  if (readtextcase(code, i, "If"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::IF;
      if (dabsic_read_if(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcase(code, i, "While"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::WHILE;
      if (dabsic_read_while(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcase(code, i, "For"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::FOR;
      if (dabsic_read_for(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcase(code, i, "Do"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::DO_WHILE;
      if (dabsic_read_do(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcase(code, i, "Repeat"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::REPEAT;
      if (dabsic_read_repeat(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcase(code, i, "Return"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::RETURN;
      if (dabsic_read_instruction(code, i, func, funcnode, root) == BD_ERROR)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A value or expression was expected after 'while' on line %d",
	   "ressource,configuration,syntax",
	   whichline(code, i)
	   );
      return (BD_OK);
    }

  if (readtextcase(code, i, "Leave"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::RETURN;
      func.value.have_value = false;
      func.value.expression = NULL;
      return (BD_OK);
    }

  if (readtextcase(code, i, "Break"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::BREAK;
      return (BD_OK);
    }

  if (readtextcase(code, i, "Continue"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::CONTINUE;
      return (BD_OK);
    }

  if (code[i] == '"' || isdigit(code[i]) || readtext(code, i, "$"))
    {
      func.command = Function::PRINT;
      return (dabsic_read_print(code, i, func, funcnode, root));
    }

  if (readtext(code, i, "!"))
    {
      func.command = Function::PRINT_ERROR;
      return (dabsic_read_print(code, i, func, funcnode, root));
    }

  return (dabsic_read_instruction(code, i, func, funcnode, root));
}
