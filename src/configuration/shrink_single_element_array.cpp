// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			shrink_single_element_array(SmallConf		&cnf)
{
  if (cnf.Size() != 1)
    return ;

  cnf = cnf[0];
  cnf.expression = cnf[0].expression;
  cnf[0].expression = NULL;
  cnf.sequence = cnf[0].sequence;
  cnf[0].sequence = NULL;
  cnf.function = cnf[0].function;
  cnf[0].function = NULL;

  delete &cnf[0];
  cnf.array.clear();
}

