// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

void			hbs::PVM110N::SetDigital(DigitalOutput	id,
						 bool		value)
{
  if (value == false)
    data_out[DIGI_OUTPUT_OFFSET] &= ~(1 << id);
  else
    data_out[DIGI_OUTPUT_OFFSET] |=  (1 << id);
}

void			hbs::PVM110N::SetDigital(unsigned char	value)
{
  data_out[DIGI_OUTPUT_OFFSET] = value;
}

