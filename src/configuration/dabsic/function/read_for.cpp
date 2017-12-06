// Jason Brillante "Daàmdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_for(const char	*code,
					ssize_t		&i,
					Function	&func,
					SmallConf	&funcnode,
					SmallConf	&root)
{
  if (expr_read_expression
      (code, i, func.value, Expression::BEOF_ASSIGNATION) == false)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
  if (readtextcase(code, i, "To") == false && readtextcase(code, i, ",") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "Expected 'to' or ',' after the 'for' first parameter on line %d",
       "ressource,configuration,syntax",
       whichline(code, i)
       );
  dabsic_read_separator(code, i);

  if (expr_read_expression
      (code, i, func.additionnal_values[0], Expression::BEOF_LOWLOGIC) == false)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
  if (readtextcase(code, i, "Step") == false && readtextcase(code, i, ",") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "Expected 'Step' or ',' after the 'for' second parameter on line %d",
       "ressource,configuration,syntax",
       whichline(code, i)
       );
  dabsic_read_separator(code, i);

  if (expr_read_expression
      (code, i, func.additionnal_values[1], Expression::BEOF_ASSIGNATION) == false)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
  if (dabsic_read_inside_function(code, i, &func, funcnode, root) == BD_ERROR)
    return (BD_ERROR);
  dabsic_read_separator(code, i);

  if (readtextcase(code, i, "EndFor") || readtextcase(code, i, "Next"))
    {
      dabsic_read_separator(code, i);
      return (BD_OK);
    }
  scream_error_if
    (return (BD_ERROR), BE_SYNTAX_ERROR,
     "EndFor or Next was expected on line %d",
     "ressource,configuration,syntax",
     whichline(code, i)
     );
  return (BD_ERROR);
}

