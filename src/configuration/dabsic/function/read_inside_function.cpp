// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_inside_function(const char	*code,
						    ssize_t	&i,
						    Function	*funcx,
						    SmallConf	&funcnode,
						    SmallConf	&root)
{
  if (funcx == NULL)
    {
      if (funcnode.function == NULL)
	try
	  {
	    funcnode.function = new Function;
	    funcnode.function->nbr_lines = 0;
	  }
	catch (...)
	  {
	    scream_error_if
	      (return (BD_ERROR), ENOMEM,
	       "Memory exhausted while processing function on line %d",
	       "ressource,configuration",
	       whichline(code, i)
	       );
	  }
      funcx = funcnode.function;
    }
  Function		&func = *funcx;
  Decision		ret;

  do
    if ((ret = dabsic_read_variable_declaration
	 (code, i, func, funcnode, root)) == BD_ERROR)
      return (BD_ERROR);
  while (ret != BD_NOT_FOUND);

  while (code[i] != '\0' && code[i] != ']'
	 && checktextcase(code, i, "Else") == false
	 && checktextcase(code, i, "EndIf") == false
	 && checktextcase(code, i, "EndWhile") == false
	 && checktextcase(code, i, "WEnd") == false
	 && checktextcase(code, i, "EndFor") == false
	 && checktextcase(code, i, "Next") == false
	 && checktextcase(code, i, "AgainIf") == false
	 && checktextcase(code, i, "Until") == false)
    {
      if (func.lines.size() <= func.nbr_lines)
	func.lines.resize(func.lines.size() + 16);
      if (dabsic_read_statement
	  (code, i, func.lines[func.nbr_lines], funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      func.nbr_lines += 1;
      dabsic_read_separator(code, i);
    }
  return (BD_OK);
}

