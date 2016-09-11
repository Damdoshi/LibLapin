// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

void			hbs::PVM110N::SetAnalog(AnalogOutput	id,
						unsigned char	value)
{
  if (id == ANAL_OUTPUT_0)
    data_out[ANAL_OUTPUT_1_OFFSET] = value;
  else
    data_out[ANAL_OUTPUT_2_OFFSET] = value;
}
