// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2023
//
// Bibliotheque Lapin

#include		"lapin_private.h"

int			bunny_top_bitstream(t_bunny_bitstream	*bs)
{
  if (bs->pin_stream_size == 0)
    return (-1);
  int			*x = &bs->pin_stream[bs->pin_stream_size / 32];
  int			ret = *x & 1;

  return (ret);
}
