// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

bool			hbs::PVM110N::ReadInputs(void)
{
  if (ReceiveCommand() == false)
    return (false);
  InBitEdit_FromSystemToUser();
  return (true);
}

