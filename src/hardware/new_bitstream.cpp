// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2023
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_new_bitstream
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 260
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Allocates a bitstream for one hardware pin.
 * @param pin_num Associated pin number.
 * @param pin_stream_capacity Capacity in bits.
 * @return-success Returns a new bitstream.
 * @return-failure Returns NULL on allocation failure.
 * @see bunny_delete_bitstream, bunny_push_bitstream
 *
 * @doc-lang fr
 * @brief Alloue un bitstream pour une broche matérielle.
 * @param pin_num Numéro de broche associé.
 * @param pin_stream_capacity Capacité en bits.
 * @return-success Renvoie un nouveau bitstream.
 * @return-failure Renvoie NULL en cas d’échec d’allocation.
 * @see bunny_delete_bitstream, bunny_push_bitstream
 */
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

