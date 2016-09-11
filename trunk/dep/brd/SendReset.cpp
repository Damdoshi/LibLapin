// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

bool			hbs::PVM110N::SendReset(void) const
{
  unsigned int		i;

  data_out[COMMAND] = CMD_RESET;
  for (i = COMMAND + 1; i < sizeof(data_out) / sizeof(data_out[0]); ++i)
    data_out[i] = 0;
  return (SendCommand());
}

