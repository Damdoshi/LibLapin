// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2023
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_top_bitstream
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 320
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Returns the oldest bit from a bitstream without removing it.
 * @param bs Bitstream to inspect.
 * @return-success Returns the oldest bit.
 * @return-failure Returns -1 if the bitstream is empty.
 * @see bunny_push_bitstream, bunny_pop_bitstream
 *
 * @doc-lang fr
 * @brief Renvoie le plus ancien bit d’un bitstream sans le retirer.
 * @param bs Bitstream à inspecter.
 * @return-success Renvoie le plus ancien bit.
 * @return-failure Renvoie -1 si le bitstream est vide.
 * @see bunny_push_bitstream, bunny_pop_bitstream
 */
int			bunny_top_bitstream(t_bunny_bitstream	*bs)
{
  if (bs->pin_stream_size == 0)
    return (-1);
  int			*x = &bs->pin_stream[bs->pin_stream_size / 32];
  int			ret = *x & 1;

  return (ret);
}
