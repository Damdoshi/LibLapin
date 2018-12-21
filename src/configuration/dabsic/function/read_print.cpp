// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_print(const char		*code,
					  ssize_t		&i,
					  Function		&func,
					  SmallConf		&funcnode,
					  SmallConf		&root)
{
  int			line;

  (void)funcnode;
  (void)root;
  do
    {
      line = whichline(code, i);
      dabsic_read_separator(code, i);
      if (expr_read_expression
	  (code, i, func.value[func.value.Size()], Expression::BEOF_TERNARY)
	  == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "An expression or value was expected on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      func.value[func.value.Size() - 1].line = line;
      dabsic_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  dabsic_read_separator(code, i);
  return (BD_OK);
}

