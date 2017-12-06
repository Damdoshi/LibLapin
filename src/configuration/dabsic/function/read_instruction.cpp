// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision			dabsic_read_instruction(const char	*code,
							ssize_t		&i,
							Function	&line,
							SmallConf	&funcnode,
							SmallConf	&root)
{
  (void)funcnode;
  (void)root;
  if (expr_read_expression
      (code, i, line.value, Expression::BEOF_ASSIGNATION) == false)
    return (BD_ERROR);
  return (BD_OK);
}

