// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			shrink_single_element_array(SmallConf		&cnf)
{
  if (cnf.Size() != 1)
    return ;
  cnf = cnf[0];
  delete &cnf[0];
  cnf.array.clear();
}

