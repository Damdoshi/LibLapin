// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2023
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_pop_bitstream
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 300
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Removes and returns the oldest bit from a bitstream.
 * @param bs Bitstream to modify.
 * @return-success Returns the removed bit.
 * @return-failure Returns -1 if the bitstream is empty.
 * @see bunny_push_bitstream, bunny_top_bitstream
 *
 * @doc-lang fr
 * @brief Retire et renvoie le plus ancien bit d’un bitstream.
 * @param bs Bitstream à modifier.
 * @return-success Renvoie le bit retiré.
 * @return-failure Renvoie -1 si le bitstream est vide.
 * @see bunny_push_bitstream, bunny_top_bitstream
 */
int			bunny_pop_bitstream(t_bunny_bitstream	*bs)
{
  if (bs->pin_stream_size == 0)
    return (-1);
  int			*x = &bs->pin_stream[bs->pin_stream_size / 32];
  int			ret = *x & 1;

  *x >>= 1;
  return (ret);
}
