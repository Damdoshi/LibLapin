// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

bool			hbs::PVM110N::GetDigital(DigitalInput	id) const
{
  return ((data_in[DIGI_INPUT] >> id) & 1);
}

unsigned char		hbs::PVM110N::GetDigital(void) const
{
  return (data_in[DIGI_INPUT]);
}
