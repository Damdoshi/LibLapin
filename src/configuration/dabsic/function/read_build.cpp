// Jason Brillante "Daàmdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_build(const char	*code,
					  ssize_t	&i,
					  Function	&func,
					  SmallConf	&funcnode,
					  SmallConf	&root)
{
  (void)root;
  (void)funcnode;
  if (expr_read_expression
      (code, i, func.value, Expression::BEOF_ASSIGNATION) == false)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
 if (readtextcase(code, i, ",") == false)
   return (BD_OK);
  dabsic_read_separator(code, i);

  if (expr_read_expression
      (code, i, func.additionnal_values[0], Expression::BEOF_ASSIGNATION) == false)
    return (BD_ERROR);

  return (BD_OK);
}

