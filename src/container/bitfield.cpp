// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include	"lapin_private.h"
/*
void		bunny_left_bitfield_rotation(t_bunny_bitfield	*bf,
					     size_t		len,
					     size_t		shift) // Merde, j'ai oublié ca.
{
  t_bunny_auto_bitfield64 *bf64 = (t_bunny_auto_bitfield64*)bf;
  t_bunny_auto_bitfield8 *bf8 = (t_bunny_auto_bitfield8*)bf;
  bool		otmp = false;
  bool		ntmp = false;
  size_t	i;

  len = len + len % 8 ? 1 : 0;
  for (i = 0; i < len / 64; ++i)
    {
      ntmp = bf64[i] & (1llu << 63) ? 1 : 0;
      bf64[i] <<= 1;
      bf64[i] |= otmp;
      otmp = ntmp;
    }
  i *= 8;
  for (; i < len / 8; ++i)
    {
      ntmp = bf8[i] & (1 << 7) ? 1 : 0;
      bf8[i] <<= 1;
      bf8[i] |= otmp;
      otmp = ntmp;
    }
  bf8[0] |= ntmp;
}

void		bunny_right_bitfield_rotation(t_bunny_bitfield	*bf,
					      size_t		len,
					      size_t		shift)
{
#warning a faire
}
*/
