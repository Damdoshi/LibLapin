// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// IO Board Driver

#include		"PVM110N.hpp"

void			hbs::PVM110N::InBitEdit_FromSystemToUser(void)
{
  unsigned char		ori = data_in[DIGI_INPUT];
  unsigned char		c = 0;

  SetBit(c, 0, GetBit(ori, 4));
  SetBit(c, 1, GetBit(ori, 5));
  SetBit(c, 2, GetBit(ori, 0));
  SetBit(c, 3, GetBit(ori, 6));
  SetBit(c, 4, GetBit(ori, 7));
  data_in[DIGI_INPUT] = c;
}

