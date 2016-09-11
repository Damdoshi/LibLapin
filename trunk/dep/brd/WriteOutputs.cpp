// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

bool			hbs::PVM110N::WriteOutputs(void) const
{
  data_out[COMMAND] = CMD_SET_ANALOG_DIGITAL;
  return (SendCommand());
}

