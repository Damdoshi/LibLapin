// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_select(const char	*code,
					   ssize_t	&i,
					   Function	&func,
					   SmallConf	&funcnode,
					   SmallConf	&root)
{
  if (expr_read_expression
      (code, i, func.value, Expression::BEOF_TERNARY) == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "A value or expression was expected after 'select' on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  dabsic_read_separator(code, i);

  while (readtextcase(code, i, "Case"))
    {
      dabsic_read_separator(code, i);
      if (func.lines.size() <= func.nbr_lines)
	func.lines.resize(func.lines.size() + 16);
      Function		&nfunc = func.lines[func.nbr_lines];

      if (expr_read_expression
	  (code, i, nfunc.value, Expression::BEOF_TERNARY) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A value or expression was expected after 'case' on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );

      dabsic_read_separator(code, i);
      if (dabsic_read_inside_function(code, i, &nfunc, funcnode, root) == BD_ERROR)
	return (BD_ERROR);
      dabsic_read_separator(code, i);
      func.nbr_lines += 1;
    }

  if (readtextcase(code, i, "EndSelect"))
    {
      dabsic_read_separator(code, i);
      return (BD_OK);
    }
  scream_error_if
    (return (BD_ERROR), BE_SYNTAX_ERROR,
     "The EndSelect token was expected on line %s:%d",
     "ressource,configuration,syntax",
     SmallConf::file_read.top().c_str(), whichline(code, i)
     );
}

