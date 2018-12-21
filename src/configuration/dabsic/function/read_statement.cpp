// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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
  func.file = SmallConf::file_read.top();

  if (readtextcasesep(code, i, "If", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::IF;
      if (dabsic_read_if(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "While", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::WHILE;
      if (dabsic_read_while(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "For", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::FOR;
      if (dabsic_read_for(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Do", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::DO_WHILE;
      if (dabsic_read_do(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Repeat", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::REPEAT;
      if (dabsic_read_repeat(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Select", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::SELECT;
      if (dabsic_read_select(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "With", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::WITH;
      if (dabsic_read_with(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Return", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::RETURN;
      if (dabsic_read_instruction(code, i, func, funcnode, root) == BD_ERROR)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A value or expression was expected after 'while' on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Build", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::BUILD;
      if (dabsic_read_build(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Delete", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::DELETE;
      if (dabsic_read_instruction(code, i, func, funcnode, root) == BD_ERROR)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A value or expression was expected after 'delete' on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Leave", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::RETURN;
      func.value.have_value = false;
      func.value.expression = NULL;
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Break", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::BREAK;
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Brake", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::BRAKE;
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Link", fieldname))
    {
      dabsic_read_separator(code, i);
      func.command = Function::LINK;
      return (BD_OK);
    }

  if (readtextcasesep(code, i, "Continue", fieldname))
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
