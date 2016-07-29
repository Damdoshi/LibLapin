// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

unsigned char		hbs::PVM110N::GetAnalog(AnalogInput	id) const
{
  if (id == ANAL_INPUT_0)
    return (data_in[ANAL_1_INPUT]);
  return (data_in[ANAL_2_INPUT]);
}

