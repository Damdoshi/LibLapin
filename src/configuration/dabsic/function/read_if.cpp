// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_if(const char	*code,
				       ssize_t		&i,
				       Function		&func,
				       SmallConf	&funcnode,
				       SmallConf	&root)
{
  if (func.command != Function::ELSE)
    {
      if (dabsic_read_instruction(code, i, func, funcnode, root) == BD_ERROR)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A value or expression was expected after 'if' on line %d",
	   whichline(code, i)
	   );
      dabsic_read_separator(code, i);
      if (readtext(code, i, "Then"))
	dabsic_read_separator(code, i);
    }

  if (dabsic_read_inside_function(code, i, &func, funcnode, root) == BD_ERROR)
    return (BD_ERROR);

  if (readtext(code, i, "EndIf"))
    {
      dabsic_read_separator(code, i);
      return (BD_OK);
    }
  else if (func.command == Function::ELSE)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The EndIf token was expected on line %d",
       whichline(code, i)
       );

  if (readtext(code, i, "Else") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "EndIf or Else/Else If was expected at the end of a If statement on line %d",
       whichline(code, i)
       );
  dabsic_read_separator(code, i);

  if (func.lines.size() <= func.nbr_lines)
    func.lines.resize(func.lines.size() + 16);
  Function		&newfunc = func.lines[func.nbr_lines];

  func.nbr_lines += 1;
  dabsic_read_separator(code, i);
  if (readtext(code, i, "If"))
    {
      newfunc.command = Function::ELSE_IF;
      return (dabsic_read_if(code, i, newfunc, funcnode, root));
    }

  newfunc.command = Function::ELSE;
  return (dabsic_read_if(code, i, newfunc, funcnode, root));
}

