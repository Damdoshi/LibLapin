// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2023
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_bitstream	*bunny_new_bitstream(int		pin_num,
					     int		pin_stream_capacity)
{
  t_bunny_bitstream	*bs;
  int			cases = pin_stream_capacity / 32 + pin_stream_capacity % 32 ? 1 : 0;

  if ((bs = (t_bunny_bitstream*)bunny_calloc(1, sizeof(*bs) + cases * sizeof(bs->pin_stream))) == NULL)
    return (NULL);
  bs->pin_number = pin_num;
  bs->pin_stream_capacity = pin_stream_capacity;
  bs->pin_stream_size = 0;
  return (bs);
}

