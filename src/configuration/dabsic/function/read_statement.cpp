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
  if (readtext(code, i, "If"))
    {
      dabsic_read_separator(code, i);
      func.command = Function::IF;
      if (dabsic_read_if(code, i, func, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      return (BD_OK);
    }

  if (readtext(code, i, "While"))
    {
      dabsic_read_separator(code, i);

    }

  if (readtext(code, i, "For"))
    {
      dabsic_read_separator(code, i);

    }

  if (readtext(code, i, "Do"))
    {
      dabsic_read_separator(code, i);

    }

  if (readtext(code, i, "Repeat"))
    {
      dabsic_read_separator(code, i);

    }

  if (readtext(code, i, "Return"))
    {
      dabsic_read_separator(code, i);

    }

  if (code[i] == '"')
    {
      func.command = Function::PRINT;
      return (dabsic_read_print(code, i, func, funcnode, root));
    }
  return (dabsic_read_instruction(code, i, func, funcnode, root));
}
