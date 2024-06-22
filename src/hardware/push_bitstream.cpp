// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2023
//
// Bibliotheque Lapin

#include		"lapin_private.h"

// Contenu du bitstream
// [HGFE DCBA] [PONM LKJI] etc.
//
// Contenu de val:
// HGFE DCBA
//

int			bunny_push_bitstream(t_bunny_bitstream		*bs,
					     size_t			nbr_bit,
					     int			val)
{
  if (nbr_bit > 32)
    return (-1);
  if (nbr_bit + bs->pin_stream_size > bs->pin_stream_capacity)
    return (-1);
  while (nbr_bit > 0)
    {
      int		*x = &bs->pin_stream[bs->pin_stream_size / 32];
      bool		v = val & 1;

      *x <<= 1;
      if (v)
	*x |= 1;
      val >>= 1;
      nbr_bit -= 1;
      bs->pin_stream_size += 1;
    }
  return (bs->pin_stream_capacity - bs->pin_stream_size);
}
