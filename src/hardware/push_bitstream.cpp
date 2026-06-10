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


/**
 * @doc
 * @doc-symbol bunny_push_bitstream
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Pushes bits at the end of a bitstream.
 * @param bs Bitstream to modify.
 * @param nbr_bit Number of low bits to push from val.
 * @param val Value containing bits to push.
 * @return-success Returns the remaining capacity in bits.
 * @return-failure Returns -1 if nbr_bit is invalid or the bitstream is full.
 * @see bunny_pop_bitstream, bunny_top_bitstream
 *
 * @doc-lang fr
 * @brief Pousse des bits à la fin d’un bitstream.
 * @param bs Bitstream à modifier.
 * @param nbr_bit Nombre de bits faibles à pousser depuis val.
 * @param val Valeur contenant les bits à pousser.
 * @return-success Renvoie la capacité restante en bits.
 * @return-failure Renvoie -1 si nbr_bit est invalide ou si le bitstream est plein.
 * @see bunny_pop_bitstream, bunny_top_bitstream
 */
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
